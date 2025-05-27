#include <iostream>
#include <vector>
#include <list>
#include <functional> // για το std::hash
#include <algorithm>  // για το std::count
using namespace std;

// Υλοποίηση πολυσυνόλου (multiset) με κατακερματισμό
template <typename T>
class HashMultiset {
private:
    // Ο πίνακας κατακερματισμού είναι ένα vector από λίστες στοιχείων
    vector<list<T>> table;
    size_t elementCount;  // Συνολικός αριθμός στοιχείων
    size_t bucketCount;   // Μέγεθος του πίνακα
    double maxLoadFactor; // Μέγιστος συντελεστής φόρτωσης
    
    // Υπολογισμός του δείκτη (index) για ένα στοιχείο
    size_t getIndex(const T& element) const {
        return std::hash<T>{}(element) % bucketCount;
    }
    
    // Επανακατανομή όταν ο πίνακας είναι πολύ γεμάτος
    void rehash() {
        size_t newSize = bucketCount * 2;
        rehash(newSize);
    }
    
    // Επανακατανομή με συγκεκριμένο μέγεθος
    void rehash(size_t newSize) {
        vector<list<T>> oldTable = table;
        
        // Δημιουργία νέου πίνακα
        table.clear();
        table.resize(newSize);
        bucketCount = newSize;
        elementCount = 0;
        
        // Επανεισαγωγή των στοιχείων
        for (const auto& bucket : oldTable) {
            for (const auto& element : bucket) {
                insert(element);
            }
        }
        
        cout << "Rehashed: Νέο μέγεθος = " << bucketCount << endl;
    }
    
public:
    // Κατασκευαστής
    HashMultiset(size_t initialSize = 10, double loadFactor = 0.75)
        : bucketCount(initialSize), elementCount(0), maxLoadFactor(loadFactor) {
        table.resize(bucketCount);
    }
    
    // Εισαγωγή στοιχείου
    void insert(const T& element) {
        // Έλεγχος αν χρειάζεται rehashing
        if (static_cast<double>(elementCount + 1) / bucketCount > maxLoadFactor) {
            rehash();
        }
        
        size_t index = getIndex(element);
        table[index].push_back(element);
        elementCount++;
    }
    
    // Έλεγχος αν υπάρχει τουλάχιστον μία εμφάνιση του στοιχείου
    bool contains(const T& element) const {
        size_t index = getIndex(element);
        
        for (const auto& item : table[index]) {
            if (item == element) {
                return true;
            }
        }
        
        return false;
    }
    
    // Μέτρηση εμφανίσεων του στοιχείου
    size_t count(const T& element) const {
        size_t index = getIndex(element);
        
        return std::count(table[index].begin(), table[index].end(), element);
    }
    
    // Διαγραφή μιας εμφάνισης του στοιχείου
    bool erase_one(const T& element) {
        size_t index = getIndex(element);
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == element) {
                table[index].erase(it);
                elementCount--;
                return true;
            }
        }
        
        return false;
    }
    
    // Διαγραφή όλων των εμφανίσεων του στοιχείου
    size_t erase_all(const T& element) {
        size_t index = getIndex(element);
        size_t countBefore = table[index].size();
        
        // Αφαίρεση όλων των εμφανίσεων του στοιχείου
        table[index].remove(element);
        
        size_t countAfter = table[index].size();
        size_t erased = countBefore - countAfter;
        elementCount -= erased;
        
        return erased;
    }
    
    // Επιστροφή του συνολικού αριθμού στοιχείων
    size_t size() const {
        return elementCount;
    }
    
    // Έλεγχος αν το πολυσύνολο είναι κενό
    bool empty() const {
        return elementCount == 0;
    }
    
    // Καθαρισμός του πολυσυνόλου
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        elementCount = 0;
    }
    
    // Επιστροφή του αριθμού των κάδων
    size_t bucket_count() const {
        return bucketCount;
    }
    
    // Επιστροφή του τρέχοντος συντελεστή φόρτωσης
    double load_factor() const {
        return static_cast<double>(elementCount) / bucketCount;
    }
    
    // Επιστροφή του μέγιστου συντελεστή φόρτωσης
    double max_load_factor() const {
        return maxLoadFactor;
    }
    
    // Ορισμός του μέγιστου συντελεστή φόρτωσης
    void max_load_factor(double ml) {
        maxLoadFactor = ml;
        if (load_factor() > maxLoadFactor) {
            rehash(bucketCount * 2);
        }
    }
    
    // Εμφάνιση στατιστικών
    void print_stats() const {
        cout << "=== HashMultiset Statistics ===" << endl;
        cout << "Αριθμός κάδων: " << bucketCount << endl;
        cout << "Συνολικός αριθμός στοιχείων: " << elementCount << endl;
        cout << "Συντελεστής φόρτωσης: " << load_factor() << endl;
        
        size_t emptyBuckets = 0;
        size_t maxBucketSize = 0;
        
        for (const auto& bucket : table) {
            if (bucket.empty()) {
                emptyBuckets++;
            } else {
                size_t bucketSize = bucket.size();
                if (bucketSize > maxBucketSize) {
                    maxBucketSize = bucketSize;
                }
            }
        }
        
        cout << "Κενοί κάδοι: " << emptyBuckets << " (" 
             << static_cast<double>(emptyBuckets) / bucketCount * 100 << "%)" << endl;
        cout << "Μέγιστο μέγεθος κάδου: " << maxBucketSize << endl;
        cout << "=============================" << endl;
    }
    
    // Εμφάνιση όλων των στοιχείων
    void print_all() const {
        cout << "Στοιχεία του HashMultiset:" << endl;
        
        for (size_t i = 0; i < bucketCount; i++) {
            if (!table[i].empty()) {
                cout << "Bucket " << i << ": ";
                for (const auto& element : table[i]) {
                    cout << element << " ";
                }
                cout << endl;
            }
        }
    }
};

// Παράδειγμα χρήσης
int main() {
    // Δημιουργία ενός multiset ακεραίων
    HashMultiset<int> numSet;
    
    // Εισαγωγή στοιχείων
    numSet.insert(10);
    numSet.insert(20);
    numSet.insert(30);
    numSet.insert(10);  // Διπλότυπο
    numSet.insert(20);  // Διπλότυπο
    numSet.insert(10);  // Τριπλότυπο
    
    // Εμφάνιση στατιστικών
    numSet.print_stats();
    
    // Εμφάνιση όλων των στοιχείων
    numSet.print_all();
    
    // Έλεγχος περιεχομένου και πλήθους
    cout << "\nΈλεγχος περιεχομένου:" << endl;
    cout << "Περιέχει το 10; " << (numSet.contains(10) ? "Ναι" : "Όχι") << endl;
    cout << "Περιέχει το 15; " << (numSet.contains(15) ? "Ναι" : "Όχι") << endl;
    
    cout << "\nΠλήθος εμφανίσεων:" << endl;
    cout << "Το 10 εμφανίζεται " << numSet.count(10) << " φορές" << endl;
    cout << "Το 20 εμφανίζεται " << numSet.count(20) << " φορές" << endl;
    cout << "Το 30 εμφανίζεται " << numSet.count(30) << " φορές" << endl;
    
    // Διαγραφή μιας εμφάνισης
    cout << "\nΔιαγραφή μιας εμφάνισης του 10:" << endl;
    numSet.erase_one(10);
    cout << "Το 10 τώρα εμφανίζεται " << numSet.count(10) << " φορές" << endl;
    
    // Διαγραφή όλων των εμφανίσεων
    cout << "\nΔιαγραφή όλων των εμφανίσεων του 20:" << endl;
    size_t erasedCount = numSet.erase_all(20);
    cout << "Διαγράφηκαν " << erasedCount << " εμφανίσεις" << endl;
    cout << "Το 20 τώρα εμφανίζεται " << numSet.count(20) << " φορές" << endl;
    
    // Εισαγωγή περισσότερων στοιχείων
    cout << "\nΕισαγωγή περισσότερων στοιχείων..." << endl;
    for (int i = 0; i < 20; i++) {
        numSet.insert(i * 5);
    }
    
    // Τελικά στατιστικά και περιεχόμενο
    numSet.print_stats();
    numSet.print_all();
    
    return 0;
}
