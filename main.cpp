#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <map>

using namespace std;

// Define the Finite Automaton class
class FiniteAutomaton {
public:
    // States, Alphabet, Transitions, Initial State, Final States
    unordered_set<int> states;
    unordered_set<char> alphabet;
    map<pair<int, char>, int> transitions;
    int initialState;
    unordered_set<int> finalStates;

    // Function to read FA elements from file
    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            exit(EXIT_FAILURE);
        }

        // Read states
        int numStates;
        file >> numStates;
        for (int i = 0; i < numStates; ++i) {
            int state;
            file >> state;
            states.insert(state);
        }

        // Read alphabet
        int numAlphabet;
        file >> numAlphabet;
        for (int i = 0; i < numAlphabet; ++i) {
            char symbol;
            file >> symbol;
            alphabet.insert(symbol);
        }

        // Read transitions
        int numTransitions;
        file >> numTransitions;
        for (int i = 0; i < numTransitions; ++i) {
            int fromState, toState;
            char symbol;
            file >> fromState >> symbol >> toState;
            transitions[{fromState, symbol}] = toState;
        }

        // Read initial state
        file >> initialState;

        // Read final states
        int numFinalStates;
        file >> numFinalStates;
        for (int i = 0; i < numFinalStates; ++i) {
            int state;
            file >> state;
            finalStates.insert(state);
        }

        file.close();
    }

    // Function to display FA elements
    void displayMenu() {
        cout << "1. Set of States: ";
        displaySet(states);
        cout << "2. Alphabet: ";
        displaySet(alphabet);
        cout << "3. Transitions: ";
        displayTransitions();
        cout << "4. Initial State: " << initialState << endl;
        cout << "5. Set of Final States: ";
        displaySet(finalStates);
    }

    // Function to check if a sequence is accepted by the DFA
    bool isSequenceAccepted(const string& sequence) {
        int currentState = initialState;
        for (char symbol : sequence) {
            if (alphabet.find(symbol) == alphabet.end()) {
                cerr << "Error: Symbol '" << symbol << "' not in alphabet." << endl;
                exit(EXIT_FAILURE);
            }

            auto it = transitions.find({currentState, symbol});
            if (it == transitions.end()) {
                return false;  // No transition for the given symbol
            }

            currentState = it->second;
        }

        return finalStates.find(currentState) != finalStates.end();
    }

private:
    // Helper function to display a set
    template<typename T>
    void displaySet(const unordered_set<T>& set) {
        for (const T& element : set) {
            cout << element << " ";
        }
        cout << endl;
    }

    // Helper function to display transitions
    void displayTransitions() {
        for (const auto& entry : transitions) {
            cout << "(" << entry.first.first << ", " << entry.first.second << ") -> " << entry.second << "; ";
        }
        cout << endl;
    }
};

int main() {
    // Read FA from file
    FiniteAutomaton fa;
    fa.readFromFile("C:\\Users\\vlads\\vlad\\facultate_an_3_1\\LFTC\\Lab4\\FA.in");


    while(true){
        // Display FA elements using a menu
        fa.displayMenu();

        // Check if a sequence is accepted by the DFA
        string sequence;
        cout << "Enter a sequence to check if it's accepted by the DFA: ";
        cin >> sequence;

        if(sequence == "exit"){
            break;
        }

        if (fa.isSequenceAccepted(sequence)) {
            cout << "Sequence is accepted by the DFA." << endl;
        } else {
            cout << "Sequence is not accepted by the DFA." << endl;
        }
    }


    return 0;
}
