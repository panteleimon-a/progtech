#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility> // για το pair
using namespace std;

// Κλάση για υλοποίηση πίνακα κατακερματισμού με κλειστή διευθυνσιοδότηση (χωριστή αλυσίδωση)
class HashTableClosed {
private:
    // Χρησιμοποιούμε λίστες από ζεύγη κλειδιού-τιμής για την αλυσίδωση
    vector<list<pair<string, string>>> table;
    int size;      // Τρέχων αριθμός στοιχείων
    int capacity;  // Μέγεθος του πίνακα
    double loadFactor; // Συντελεστής φόρτωσης για rehashing
    
    // Συνάρτηση κατακερματισμού για συμβολοσειρές
    // Χρησιμοποιούμε τον αλγόριθμο DJB2
    unsigned int hashFunction(const string& key) const {
        unsigned int hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % capacity;
    }
    
    // Επανακατανομή για αύξηση του μεγέθους του πίνακα
    void rehash() {
        int oldCapacity = capacity;
        vector<list<pair<string, string>>> oldTable = table;
        
        // Διπλασιάζουμε το μέγεθος του πίνακα
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        size = 0;
        
        // Επανεισαγωγή των στοιχείων
        for (int i = 0; i < oldCapacity; i++) {
            for (const auto& entry : oldTable[i]) {
                insert(entry.first, entry.second);
            }
        }
        
        cout << "Rehashed: Νέο μέγεθος = " << capacity << endl;
    }
    
public:
    // Κατασκευαστής
    HashTableClosed(int initialCapacity = 10, double loadFactor = 2.0) 
        : capacity(initialCapacity), size(0), loadFactor(loadFactor) {
        table.resize(capacity);
    }
    
    // Εισαγωγή ζεύγους κλειδιού-τιμής
    void insert(const string& key, const string& value) {
        // Έλεγχος αν χρειάζεται rehashing
        if ((double)size / capacity >= loadFactor) {
            rehash();
        }
        
        unsigned int index = hashFunction(key);
        
        // Έλεγχος αν το κλειδί υπάρχει ήδη
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value; // Ενημέρωση της τιμής
                return;
            }
        }
        
        // Εισαγωγή νέου ζεύγους
        table[index].push_back(make_pair(key, value));
        size++;
    }
    
    // Αναζήτηση τιμής με βάση το κλειδί
    bool search(const string& key, string& value) const {
        unsigned int index = hashFunction(key);
        
        for (const auto& entry : table[index]) {
            if (entry.first == key) {
                value = entry.second;
                return true;
            }
        }
        
        return false;
    }
    
    // Διαγραφή ζεύγους με βάση το κλειδί
    bool remove(const string& key) {
        unsigned int index = hashFunction(key);
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                size--;
                return true;
            }
        }
        
        return false;
    }
    
    // Εμφάνιση του πίνακα
    void display() const {
        cout << "Hash Table (Κλειστή Διευθυνσιοδότηση με Χωριστή Αλυσίδωση):" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            if (table[i].empty()) {
                cout << "<κενό>" << endl;
            } else {
                for (const auto& entry : table[i]) {
                    cout << "(" << entry.first << ", " << entry.second << ") ";
                }
                cout << endl;
            }
        }
        cout << "Μέγεθος: " << size << ", Χωρητικότητα: " << capacity << endl;
    }
    
    // Επιστροφή του τρέχοντος μεγέθους
    int getSize() const {
        return size;
    }
    
    // Επιστροφή της τρέχουσας χωρητικότητας
    int getCapacity() const {
        return capacity;
    }
    
    // Επιστροφή του μέγιστου μήκους αλυσίδας
    int getMaxChainLength() const {
        int maxLength = 0;
        for (const auto& chain : table) {
            int length = chain.size();
            if (length > maxLength) {
                maxLength = length;
            }
        }
        return maxLength;
    }
};

// Παράδειγμα χρήσης
int main() {
    HashTableClosed hashMap(7);  // Αρχικό μέγεθος 7
    
    // Εισαγωγή ζευγών κλειδιού-τιμής
    hashMap.insert("one", "ένα");
    hashMap.insert("two", "δύο");
    hashMap.insert("three", "τρία");
    hashMap.insert("four", "τέσσερα");
    hashMap.insert("five", "πέντε");
    hashMap.insert("six", "έξι");
    hashMap.insert("seven", "επτά");
    
    // Εμφάνιση του πίνακα
    hashMap.display();
    
    // Αναζήτηση τιμών
    string value;
    cout << "\nΑναζήτηση 'three': ";
    if (hashMap.search("three", value)) {
        cout << "Βρέθηκε με τιμή: " << value << endl;
    } else {
        cout << "Δεν βρέθηκε" << endl;
    }
    
    cout << "Αναζήτηση 'eight': ";
    if (hashMap.search("eight", value)) {
        cout << "Βρέθηκε με τιμή: " << value << endl;
    } else {
        cout << "Δεν βρέθηκε" << endl;
    }
    
    // Ενημέρωση τιμής
    cout << "\nΕνημέρωση 'five' σε 'πέντε (5)'" << endl;
    hashMap.insert("five", "πέντε (5)");
    
    // Διαγραφή ζεύγους
    cout << "Διαγραφή 'three': " << (hashMap.remove("three") ? "Επιτυχής" : "Ανεπιτυχής") << endl;
    
    // Εμφάνιση του πίνακα μετά τις αλλαγές
    hashMap.display();
    
    // Προσθήκη περισσότερων στοιχείων για να προκληθεί rehashing
    cout << "\nΕισαγωγή περισσότερων στοιχείων..." << endl;
    hashMap.insert("eight", "οκτώ");
    hashMap.insert("nine", "εννέα");
    hashMap.insert("ten", "δέκα");
    hashMap.insert("eleven", "έντεκα");
    hashMap.insert("twelve", "δώδεκα");
    hashMap.insert("thirteen", "δεκατρία");
    hashMap.insert("fourteen", "δεκατέσσερα");
    
    // Εμφάνιση του πίνακα μετά το rehashing
    hashMap.display();
    
    // Εμφάνιση του μέγιστου μήκους αλυσίδας
    cout << "\nΜέγιστο μήκος αλυσίδας: " << hashMap.getMaxChainLength() << endl;
    
    return 0;
}
