#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <algorithm>
using namespace std;

// Διάφορες συναρτήσεις κατακερματισμού για συμβολοσειρές

// 1. Απλό άθροισμα των τιμών ASCII των χαρακτήρων
unsigned int simpleASCIISum(const string& str) {
    unsigned int hash = 0;
    for (char c : str) {
        hash += (unsigned char)c;
    }
    return hash;
}

// 2. Συνάρτηση πολλαπλασιασμού - Shift
unsigned int shiftMultiply(const string& str) {
    unsigned int hash = 0;
    for (char c : str) {
        hash = (hash << 5) + hash + (unsigned char)c;
    }
    return hash;
}

// 3. Αλγόριθμος DJB2
unsigned int djb2(const string& str) {
    unsigned int hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + (unsigned char)c; // hash * 33 + c
    }
    return hash;
}

// 4. Αλγόριθμος SDBM
unsigned int sdbm(const string& str) {
    unsigned int hash = 0;
    for (char c : str) {
        hash = (unsigned char)c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

// 5. Αλγόριθμος FNV-1a
unsigned int fnv1a(const string& str) {
    const unsigned int FNV_PRIME = 16777619;
    const unsigned int FNV_OFFSET_BASIS = 2166136261;
    
    unsigned int hash = FNV_OFFSET_BASIS;
    for (char c : str) {
        hash ^= (unsigned char)c;
        hash *= FNV_PRIME;
    }
    return hash;
}

// Κλάση για τη σύγκριση συναρτήσεων κατακερματισμού
class HashFunctionComparer {
private:
    // Δομή για την αποθήκευση μιας συνάρτησης κατακερματισμού και του ονόματός της
    struct HashFunction {
        string name;
        function<unsigned int(const string&)> func;
        
        HashFunction(const string& n, function<unsigned int(const string&)> f)
            : name(n), func(f) {}
    };
    
    vector<HashFunction> hashFunctions;
    
    // Δομή για την αποθήκευση των αποτελεσμάτων της αξιολόγησης
    struct EvaluationResult {
        string functionName;
        unsigned int totalCollisions;
        unsigned int maxCollisions;
        double avgCollisionsPerBucket;
        double emptyBucketsPercent;
        double executionTimeMs;
        
        // Κατασκευαστής για εύκολη δημιουργία
        EvaluationResult(string name, unsigned int total, unsigned int max, 
                         double avg, double empty, double time)
            : functionName(name), totalCollisions(total), maxCollisions(max),
              avgCollisionsPerBucket(avg), emptyBucketsPercent(empty),
              executionTimeMs(time) {}
    };
    
public:
    // Προσθήκη μιας συνάρτησης κατακερματισμού
    void addHashFunction(const string& name, function<unsigned int(const string&)> func) {
        hashFunctions.push_back(HashFunction(name, func));
    }
    
    // Αξιολόγηση των συναρτήσεων κατακερματισμού με ένα σύνολο δεδομένων
    void evaluate(const vector<string>& data, size_t tableSize) {
        vector<EvaluationResult> results;
        
        cout << "Αξιολόγηση συναρτήσεων κατακερματισμού" << endl;
        cout << "Πλήθος στοιχείων δεδομένων: " << data.size() << endl;
        cout << "Μέγεθος πίνακα κατακερματισμού: " << tableSize << endl;
        cout << "Ιδανικός συντελεστής φόρτωσης: " << (double)data.size() / tableSize << endl;
        cout << "------------------------------------------------------" << endl;
        
        for (const auto& hashFunc : hashFunctions) {
            // Μέτρηση του χρόνου εκτέλεσης
            auto startTime = chrono::high_resolution_clock::now();
            
            // Υπολογισμός των τιμών κατακερματισμού και καταμέτρηση συγκρούσεων
            vector<vector<string>> hashTable(tableSize);
            
            for (const auto& item : data) {
                unsigned int hash = hashFunc.func(item) % tableSize;
                hashTable[hash].push_back(item);
            }
            
            auto endTime = chrono::high_resolution_clock::now();
            double timeMs = chrono::duration<double, milli>(endTime - startTime).count();
            
            // Υπολογισμός στατιστικών
            unsigned int totalCollisions = 0;
            unsigned int maxCollisions = 0;
            unsigned int nonEmptyBuckets = 0;
            
            for (const auto& bucket : hashTable) {
                if (bucket.size() > 0) {
                    nonEmptyBuckets++;
                }
                if (bucket.size() > 1) {
                    totalCollisions += (bucket.size() - 1);
                }
                if (bucket.size() > maxCollisions) {
                    maxCollisions = bucket.size();
                }
            }
            
            double avgCollisionsPerBucket = (double)totalCollisions / nonEmptyBuckets;
            double emptyBucketsPercent = (double)(tableSize - nonEmptyBuckets) / tableSize * 100;
            
            // Αποθήκευση των αποτελεσμάτων
            results.push_back(EvaluationResult(
                hashFunc.name, totalCollisions, maxCollisions,
                avgCollisionsPerBucket, emptyBucketsPercent, timeMs
            ));
        }
        
        // Εμφάνιση των αποτελεσμάτων
        cout << setw(20) << left << "Συνάρτηση" 
             << setw(15) << right << "Συγκρούσεις" 
             << setw(15) << "Μεγ. Συγκρ." 
             << setw(15) << "Μ.Ο. Συγκρ." 
             << setw(15) << "% Κενοί Κάδοι" 
             << setw(15) << "Χρόνος (ms)" << endl;
        cout << string(95, '-') << endl;
        
        // Ταξινόμηση των αποτελεσμάτων με βάση τον αριθμό των συγκρούσεων
        sort(results.begin(), results.end(), 
             [](const EvaluationResult& a, const EvaluationResult& b) {
                 return a.totalCollisions < b.totalCollisions;
             });
        
        for (const auto& result : results) {
            cout << setw(20) << left << result.functionName 
                 << setw(15) << right << result.totalCollisions 
                 << setw(15) << result.maxCollisions 
                 << setw(15) << fixed << setprecision(2) << result.avgCollisionsPerBucket 
                 << setw(15) << fixed << setprecision(2) << result.emptyBucketsPercent 
                 << setw(15) << fixed << setprecision(2) << result.executionTimeMs << endl;
        }
    }
    
    // Δημιουργία τυχαίων δεδομένων για δοκιμή
    static vector<string> generateRandomData(size_t count, size_t minLength, size_t maxLength) {
        vector<string> data;
        const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        
        // Χρήση τυχαίου σπόρου
        srand(static_cast<unsigned int>(time(nullptr)));
        
        for (size_t i = 0; i < count; i++) {
            size_t length = minLength + rand() % (maxLength - minLength + 1);
            string str;
            for (size_t j = 0; j < length; j++) {
                str += chars[rand() % chars.length()];
            }
            data.push_back(str);
        }
        
        return data;
    }
    
    // Φόρτωση δεδομένων από αρχείο
    static vector<string> loadDataFromFile(const string& filename) {
        vector<string> data;
        ifstream file(filename);
        
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (!line.empty()) {
                    data.push_back(line);
                }
            }
            file.close();
        } else {
            cerr << "Σφάλμα: Δεν είναι δυνατό το άνοιγμα του αρχείου " << filename << endl;
        }
        
        return data;
    }
};

int main() {
    HashFunctionComparer comparer;
    
    // Προσθήκη συναρτήσεων κατακερματισμού για σύγκριση
    comparer.addHashFunction("ASCII Sum", simpleASCIISum);
    comparer.addHashFunction("Shift-Multiply", shiftMultiply);
    comparer.addHashFunction("DJB2", djb2);
    comparer.addHashFunction("SDBM", sdbm);
    comparer.addHashFunction("FNV-1a", fnv1a);
    comparer.addHashFunction("std::hash", [](const string& s) { return std::hash<string>{}(s); });
    
    // Τρία διαφορετικά σενάρια δοκιμής
    
    // 1. Τυχαίες συμβολοσειρές
    cout << "\n=== ΣΕΝΑΡΙΟ 1: Τυχαίες συμβολοσειρές ===" << endl;
    vector<string> randomData = HashFunctionComparer::generateRandomData(10000, 5, 15);
    comparer.evaluate(randomData, 1000);
    
    // 2. Παρόμοιες συμβολοσειρές (χειρότερη περίπτωση)
    cout << "\n=== ΣΕΝΑΡΙΟ 2: Παρόμοιες συμβολοσειρές ===" << endl;
    vector<string> similarData;
    for (int i = 0; i < 10000; i++) {
        // Συμβολοσειρές που διαφέρουν μόνο στους τελευταίους χαρακτήρες
        similarData.push_back("user" + to_string(i));
    }
    comparer.evaluate(similarData, 1000);
    
    // 3. Αριθμητικές συμβολοσειρές
    cout << "\n=== ΣΕΝΑΡΙΟ 3: Αριθμητικές συμβολοσειρές ===" << endl;
    vector<string> numericData;
    for (int i = 0; i < 10000; i++) {
        numericData.push_back(to_string(i));
    }
    comparer.evaluate(numericData, 1000);
    
    // Προαιρετικά: Δοκιμή με πραγματικά δεδομένα από αρχείο
    string filename = "/Users/pante/Repos/progtech_old/archive/problems_w_STL/words.txt";
    vector<string> fileData = HashFunctionComparer::loadDataFromFile(filename);
    
    if (!fileData.empty()) {
        cout << "\n=== ΣΕΝΑΡΙΟ 4: Δεδομένα από αρχείο ===" << endl;
        comparer.evaluate(fileData, 1000);
    }
    
    return 0;
}
