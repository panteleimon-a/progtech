#include <iostream>
#include <vector>
#include <iomanip>
#include <optional>
using namespace std;

// Κλάση που υλοποιεί τον αλγόριθμο κατακερματισμού κούκου
class CuckooHashTable {
private:
    vector<optional<int>> table1;
    vector<optional<int>> table2;
    int size;      // Αριθμός στοιχείων
    int capacity;  // Μέγεθος πίνακα
    int max_relocations; // Μέγιστος αριθμός ανακατατάξεων πριν το rehashing
    
    // Συναρτήσεις κατακερματισμού
    int h1(int key) const {
        return key % capacity;
    }
    
    int h2(int key) const {
        return (key / capacity) % capacity;
    }
    
    // Ανακατακερματισμός (rehashing) - εδώ απλά θα εμφανίσουμε μήνυμα
    // καθώς η πλήρης υλοποίηση θα απαιτούσε νέες συναρτήσεις κατακερματισμού
    void rehash() {
        cout << "Ανακατακερματισμός (rehashing) απαιτείται!" << endl;
        cout << "Σε μια πλήρη υλοποίηση, θα επιλέγαμε νέες συναρτήσεις κατακερματισμού." << endl;
    }
    
public:
    // Κατασκευαστής
    CuckooHashTable(int m) : capacity(m), size(0), max_relocations(2 * m) {
        table1.resize(capacity);
        table2.resize(capacity);
    }
    
    // Εισαγωγή στοιχείου
    bool insert(int key, bool is_rehashing = false) {
        // Έλεγχος αν το κλειδί υπάρχει ήδη
        if (contains(key)) {
            return true;
        }
        
        // Αποθήκευση του αρχικού κλειδιού για ανίχνευση κύκλων
        int original_key = key;
        
        // Μετρητής ανακατατάξεων
        int relocations = 0;
        int relocations_count = 0; // Για στατιστικά
        
        // Προσπάθεια εισαγωγής με πιθανές ανακατατάξεις
        while (relocations < max_relocations) {
            // Προσπάθεια εισαγωγής στον πρώτο πίνακα
            int pos1 = h1(key);
            if (!table1[pos1].has_value()) {
                table1[pos1] = key;
                size++;
                cout << "Εισαγωγή κλειδιού " << key << " στον πίνακα 1, θέση " << pos1;
                if (relocations_count > 0) {
                    cout << " (μετά από " << relocations_count << " ανακατατάξεις)";
                }
                cout << endl;
                return true;
            }
            
            // Ανταλλαγή με το στοιχείο στον πρώτο πίνακα
            int temp = table1[pos1].value();
            table1[pos1] = key;
            key = temp;
            relocations++;
            relocations_count++;
            
            cout << "Ανακατάταξη: το κλειδί " << key << " εκτοπίζεται από τον πίνακα 1, θέση " << pos1 << endl;
            
            // Έλεγχος για κύκλο (επιστροφή στο αρχικό κλειδί)
            if (key == original_key && !is_rehashing) {
                // Σε περίπτωση κύκλου, κάνουμε rehashing
                cout << "Ανιχνεύθηκε κύκλος - το κλειδί " << key << " επέστρεψε στην αρχική του θέση." << endl;
                rehash();
                return false;
            }
            
            // Προσπάθεια εισαγωγής στον δεύτερο πίνακα
            int pos2 = h2(key);
            if (!table2[pos2].has_value()) {
                table2[pos2] = key;
                size++;
                cout << "Εισαγωγή κλειδιού " << key << " στον πίνακα 2, θέση " << pos2;
                if (relocations_count > 0) {
                    cout << " (μετά από " << relocations_count << " ανακατατάξεις)";
                }
                cout << endl;
                return true;
            }
            
            // Ανταλλαγή με το στοιχείο στον δεύτερο πίνακα
            temp = table2[pos2].value();
            table2[pos2] = key;
            key = temp;
            relocations++;
            relocations_count++;
            
            cout << "Ανακατάταξη: το κλειδί " << key << " εκτοπίζεται από τον πίνακα 2, θέση " << pos2 << endl;
            
            // Έλεγχος για κύκλο (επιστροφή στο αρχικό κλειδί)
            if (key == original_key && !is_rehashing) {
                // Σε περίπτωση κύκλου, κάνουμε rehashing
                cout << "Ανιχνεύθηκε κύκλος - το κλειδί " << key << " επέστρεψε στην αρχική του θέση." << endl;
                rehash();
                return false;
            }
        }
        
        // Αν φτάσουμε εδώ, έχουμε υπερβεί το μέγιστο αριθμό ανακατατάξεων
        if (!is_rehashing) {
            cout << "Υπέρβαση μέγιστου αριθμού ανακατατάξεων για το κλειδί " << key << "." << endl;
            rehash();
        }
        return false;
    }
    
    // Αναζήτηση στοιχείου
    bool contains(int key) const {
        int lookups = 0;
        
        // Έλεγχος στον πρώτο πίνακα
        int pos1 = h1(key);
        lookups++;
        if (table1[pos1].has_value() && table1[pos1].value() == key) {
            cout << "Το κλειδί " << key << " βρέθηκε στον πίνακα 1, θέση " << pos1 << " (αναζητήσεις: " << lookups << ")" << endl;
            return true;
        }
        
        // Έλεγχος στον δεύτερο πίνακα
        int pos2 = h2(key);
        lookups++;
        if (table2[pos2].has_value() && table2[pos2].value() == key) {
            cout << "Το κλειδί " << key << " βρέθηκε στον πίνακα 2, θέση " << pos2 << " (αναζητήσεις: " << lookups << ")" << endl;
            return true;
        }
        
        // Το κλειδί δεν βρέθηκε
        cout << "Το κλειδί " << key << " δεν βρέθηκε (αναζητήσεις: " << lookups << ")" << endl;
        return false;
    }
    
    // Εμφάνιση των πινάκων
    void display() const {
        cout << "\nΠίνακες κατακερματισμού κούκου (μέγεθος: " << capacity << ", στοιχεία: " << size << "):" << endl;
        
        // Επικεφαλίδα
        cout << setw(5) << "Θέση" << " | " << setw(7) << "Πίνακας 1" << " | " << setw(7) << "Πίνακας 2" << endl;
        cout << string(23, '-') << endl;
        
        // Περιεχόμενα των πινάκων
        for (int i = 0; i < capacity; i++) {
            cout << setw(5) << i << " | ";
            
            if (table1[i].has_value()) {
                cout << setw(7) << table1[i].value();
            } else {
                cout << setw(7) << "<κενό>";
            }
            
            cout << " | ";
            
            if (table2[i].has_value()) {
                cout << setw(7) << table2[i].value();
            } else {
                cout << setw(7) << "<κενό>";
            }
            
            cout << endl;
        }
    }
};

int main() {
    const int TABLE_SIZE = 11;
    
    // Δημιουργία πίνακα κατακερματισμού κούκου
    CuckooHashTable hashTable(TABLE_SIZE);
    
    // Κλειδιά προς εισαγωγή
    vector<int> keys = {23, 45, 67, 89, 11, 33, 55, 77, 99};
    
    cout << "=== Εισαγωγή κλειδιών ===" << endl;
    for (int key : keys) {
        hashTable.insert(key);
    }
    
    // Εμφάνιση των πινάκων
    hashTable.display();
    
    cout << "\n=== Αναζήτηση κλειδιών ===" << endl;
    hashTable.contains(45);  // Υπάρχει
    hashTable.contains(78);  // Δεν υπάρχει
    hashTable.contains(99);  // Υπάρχει
    
    return 0;
}
