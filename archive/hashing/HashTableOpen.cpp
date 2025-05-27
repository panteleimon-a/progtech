#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// Κλάση για υλοποίηση πίνακα κατακερματισμού με ανοιχτή διευθυνσιοδότηση
class HashTableOpen {
private:
    // Δομή για τα στοιχεία του πίνακα
    struct HashEntry {
        int key;
        bool isDeleted;
        bool isEmpty;
        
        HashEntry() : isEmpty(true), isDeleted(false) {}
    };
    
    vector<HashEntry> table;
    int size;      // Τρέχων αριθμός στοιχείων
    int capacity;  // Μέγεθος του πίνακα
    double loadFactor;  // Συντελεστής φόρτωσης για rehashing
    
    // Συνάρτηση κατακερματισμού
    int hashFunction(int key) const {
        return abs(key) % capacity;
    }
    
    // Επανακατανομή για αύξηση του μεγέθους του πίνακα
    void rehash() {
        int oldCapacity = capacity;
        vector<HashEntry> oldTable = table;
        
        // Διπλασιάζουμε το μέγεθος του πίνακα
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        size = 0;
        
        // Επανεισαγωγή των στοιχείων
        for (int i = 0; i < oldCapacity; i++) {
            if (!oldTable[i].isEmpty && !oldTable[i].isDeleted) {
                insert(oldTable[i].key);
            }
        }
        
        cout << "Rehashed: Νέο μέγεθος = " << capacity << endl;
    }
    
public:
    // Κατασκευαστής
    HashTableOpen(int initialCapacity = 10, double loadFactor = 0.7) 
        : capacity(initialCapacity), size(0), loadFactor(loadFactor) {
        table.resize(capacity);
    }
    
    // Εισαγωγή στοιχείου
    bool insert(int key) {
        // Έλεγχος αν χρειάζεται rehashing
        if ((double)size / capacity >= loadFactor) {
            rehash();
        }
        
        int hash = hashFunction(key);
        int i = 0;
        
        // Γραμμική διερεύνηση για εύρεση κενής θέσης
        while (i < capacity) {
            int index = (hash + i) % capacity;
            
            // Αν η θέση είναι κενή ή έχει διαγραφεί
            if (table[index].isEmpty || table[index].isDeleted) {
                table[index].key = key;
                table[index].isEmpty = false;
                table[index].isDeleted = false;
                size++;
                return true;
            }
            
            // Αν το κλειδί υπάρχει ήδη
            if (table[index].key == key && !table[index].isDeleted) {
                return false;  // Δεν επιτρέπονται διπλότυπα
            }
            
            i++;
        }
        
        return false;  // Ο πίνακας είναι γεμάτος (σπάνια περίπτωση)
    }
    
    // Αναζήτηση στοιχείου
    bool search(int key) const {
        int hash = hashFunction(key);
        int i = 0;
        
        while (i < capacity) {
            int index = (hash + i) % capacity;
            
            // Αν η θέση είναι κενή, το στοιχείο δεν υπάρχει
            if (table[index].isEmpty) {
                return false;
            }
            
            // Αν βρέθηκε το κλειδί και δεν είναι διαγραμμένο
            if (table[index].key == key && !table[index].isDeleted) {
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    // Διαγραφή στοιχείου
    bool remove(int key) {
        int hash = hashFunction(key);
        int i = 0;
        
        while (i < capacity) {
            int index = (hash + i) % capacity;
            
            // Αν η θέση είναι κενή, το στοιχείο δεν υπάρχει
            if (table[index].isEmpty) {
                return false;
            }
            
            // Αν βρέθηκε το κλειδί και δεν είναι διαγραμμένο
            if (table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true;
                size--;
                return true;
            }
            
            i++;
        }
        
        return false;
    }
    
    // Εμφάνιση του πίνακα
    void display() const {
        cout << "Hash Table (Ανοιχτή Διευθυνσιοδότηση):" << endl;
        for (int i = 0; i < capacity; i++) {
            if (!table[i].isEmpty && !table[i].isDeleted) {
                cout << i << ": " << table[i].key << endl;
            } else if (table[i].isDeleted) {
                cout << i << ": <διαγραμμένο>" << endl;
            } else {
                cout << i << ": <κενό>" << endl;
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
};

// Παράδειγμα χρήσης
int main() {
    HashTableOpen hashTable(7);  // Αρχικό μέγεθος 7
    
    // Εισαγωγή στοιχείων
    hashTable.insert(5);
    hashTable.insert(28);
    hashTable.insert(19);
    hashTable.insert(15);
    hashTable.insert(20);
    hashTable.insert(33);
    
    // Εμφάνιση του πίνακα
    hashTable.display();
    
    // Αναζήτηση στοιχείων
    cout << "\nΑναζήτηση 15: " << (hashTable.search(15) ? "Βρέθηκε" : "Δεν βρέθηκε") << endl;
    cout << "Αναζήτηση 10: " << (hashTable.search(10) ? "Βρέθηκε" : "Δεν βρέθηκε") << endl;
    
    // Διαγραφή στοιχείου
    cout << "\nΔιαγραφή 15: " << (hashTable.remove(15) ? "Επιτυχής" : "Ανεπιτυχής") << endl;
    
    // Εμφάνιση του πίνακα μετά τη διαγραφή
    hashTable.display();
    
    // Αναζήτηση μετά τη διαγραφή
    cout << "\nΑναζήτηση 15 μετά τη διαγραφή: " << (hashTable.search(15) ? "Βρέθηκε" : "Δεν βρέθηκε") << endl;
    
    // Εισαγωγή περισσότερων στοιχείων για να προκληθεί rehashing
    cout << "\nΕισαγωγή περισσότερων στοιχείων..." << endl;
    hashTable.insert(40);
    hashTable.insert(7);
    hashTable.insert(14);
    hashTable.insert(21);
    
    // Εμφάνιση του πίνακα μετά το rehashing
    hashTable.display();
    
    return 0;
}
