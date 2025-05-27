#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

// Κλάση που υλοποιεί την καθολική οικογένεια συναρτήσεων κατακερματισμού
class UniversalHashFunction {
private:
    int a;      // Συντελεστής a (1 <= a < p)
    int b;      // Συντελεστής b (0 <= b < p)
    int p;      // Πρώτος αριθμός > max_key
    int m;      // Μέγεθος πίνακα
    
public:
    // Κατασκευαστής που επιλέγει τυχαία τους συντελεστές
    UniversalHashFunction(int max_key, int table_size) : m(table_size) {
        // Επιλέγουμε ένα πρώτο αριθμό μεγαλύτερο από το μέγιστο κλειδί
        p = findNextPrime(max_key);
        
        // Τυχαία επιλογή των συντελεστών a και b
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist_a(1, p - 1);
        uniform_int_distribution<int> dist_b(0, p - 1);
        
        a = dist_a(gen);
        b = dist_b(gen);
    }
    
    // Συνάρτηση κατακερματισμού h(k) = ((a*k + b) mod p) mod m
    int hash(int key) const {
        // Χρησιμοποιούμε long long για να αποφύγουμε υπερχείλιση
        long long result = (static_cast<long long>(a) * key + b) % p;
        return static_cast<int>(result % m);
    }
    
    // Εμφάνιση των παραμέτρων της συνάρτησης
    void displayParams() const {
        cout << "Παράμετροι συνάρτησης κατακερματισμού:" << endl;
        cout << "a = " << a << ", b = " << b << ", p = " << p << ", m = " << m << endl;
        cout << "h(k) = ((a*k + b) mod p) mod m = ((" << a << "*k + " << b << ") mod " << p << ") mod " << m << endl;
    }
    
private:
    // Έλεγχος αν ένας αριθμός είναι πρώτος
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
    
    // Εύρεση του επόμενου πρώτου αριθμού >= n
    int findNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }
};

// Κλάση που υλοποιεί πίνακα κατακερματισμού με αλυσίδωση
class HashTableChaining {
private:
    vector<list<int>> table;
    int size;      // Αριθμός στοιχείων
    int capacity;  // Μέγεθος πίνακα
    UniversalHashFunction hash_function;
    
public:
    // Κατασκευαστής
    HashTableChaining(int max_key, int m) 
        : capacity(m), size(0), hash_function(max_key, m) {
        table.resize(capacity);
    }
    
    // Εισαγωγή στοιχείου
    void insert(int key) {
        int index = hash_function.hash(key);
        
        // Έλεγχος αν το κλειδί υπάρχει ήδη
        for (int value : table[index]) {
            if (value == key) {
                return; // Το κλειδί υπάρχει ήδη
            }
        }
        
        // Εισαγωγή του κλειδιού στη λίστα
        table[index].push_back(key);
        size++;
    }
    
    // Εμφάνιση του πίνακα
    void display() const {
        cout << "Πίνακας κατακερματισμού με αλυσίδωση (μέγεθος: " << capacity << ", στοιχεία: " << size << "):" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << setw(2) << i << ": ";
            if (table[i].empty()) {
                cout << "<κενό>";
            } else {
                for (int key : table[i]) {
                    cout << key << " -> ";
                }
                cout << "null";
            }
            cout << endl;
        }
    }
    
    // Εμφάνιση των παραμέτρων της συνάρτησης κατακερματισμού
    void displayHashFunction() const {
        hash_function.displayParams();
    }
    
    // Υπολογισμός του μέσου μήκους αλυσίδας
    double getAverageChainLength() const {
        if (size == 0) return 0.0;
        
        int non_empty_buckets = 0;
        for (const auto& chain : table) {
            if (!chain.empty()) {
                non_empty_buckets++;
            }
        }
        
        if (non_empty_buckets == 0) return 0.0;
        return static_cast<double>(size) / non_empty_buckets;
    }
    
    // Υπολογισμός του μέγιστου μήκους αλυσίδας
    int getMaxChainLength() const {
        int max_length = 0;
        for (const auto& chain : table) {
            int length = chain.size();
            if (length > max_length) {
                max_length = length;
            }
        }
        return max_length;
    }
    
    // Υπολογισμός της τυπικής απόκλισης του μήκους αλυσίδας
    double getChainLengthStdDev() const {
        if (size == 0) return 0.0;
        
        double mean = getAverageChainLength();
        double sum_squared_diff = 0.0;
        int non_empty_buckets = 0;
        
        for (const auto& chain : table) {
            if (!chain.empty()) {
                non_empty_buckets++;
                double diff = chain.size() - mean;
                sum_squared_diff += diff * diff;
            }
        }
        
        if (non_empty_buckets <= 1) return 0.0;
        return sqrt(sum_squared_diff / non_empty_buckets);
    }
};

int main() {
    const int TABLE_SIZE = 13;
    const int MAX_KEY = 100;
    const int NUM_KEYS = 20;
    
    // Αρχικοποίηση της γεννήτριας τυχαίων αριθμών
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, MAX_KEY);
    
    // Δημιουργία του πίνακα κατακερματισμού
    HashTableChaining hashTable(MAX_KEY, TABLE_SIZE);
    
    // Εμφάνιση των παραμέτρων της συνάρτησης κατακερματισμού
    hashTable.displayHashFunction();
    
    // Δημιουργία και εισαγωγή τυχαίων κλειδιών
    vector<int> keys;
    cout << "\nΔημιουργία " << NUM_KEYS << " τυχαίων κλειδιών:" << endl;
    for (int i = 0; i < NUM_KEYS; i++) {
        int key = dist(gen);
        keys.push_back(key);
        cout << key << " ";
        hashTable.insert(key);
    }
    cout << endl;
    
    // Εμφάνιση του πίνακα κατακερματισμού
    cout << endl;
    hashTable.display();
    
    // Υπολογισμός και εμφάνιση στατιστικών
    cout << "\nΣτατιστικά πίνακα:" << endl;
    cout << "Μέσο μήκος αλυσίδας: " << fixed << setprecision(2) << hashTable.getAverageChainLength() << endl;
    cout << "Μέγιστο μήκος αλυσίδας: " << hashTable.getMaxChainLength() << endl;
    cout << "Τυπική απόκλιση μήκους αλυσίδας: " << fixed << setprecision(2) << hashTable.getChainLengthStdDev() << endl;
    
    return 0;
}
