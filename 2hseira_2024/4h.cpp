#include <stdexcept>  
#include <iostream>  
  
using namespace std;  
  
class Move {  
  public:  
    //Take sc coins from heap sh and put tc coins to heap th.  
    Move(int sh, int sc, int th, int tc) {  
      shA = sh; scA = sc; thA = th; tcA = tc;  
    };  
  
    int getSource() const {  
      return shA;  
    };  
  
    int getSourceCoins() const {  
      return scA;  
    };  
  
    int getTarget() const {  
      return thA;  
    };  
  
    int getTargetCoins() const {  
      return tcA;  
    };  
  
    friend ostream & operator << (ostream &out, const Move &move) {  
      out << "takes " << move.getSourceCoins() << " coins from heap ";  
      out << move.getSource() << " and puts ";  
  
      if (move.getTargetCoins() == 0) {  
        out << "nothing";  
      }  
      else {  
        out << move.getTargetCoins() << " coins to heap " << move.getTarget();  
      }  
      return out;  
    };  
  
  private:  
    int scA, shA, thA, tcA;  
};  
  
class State {  
  public:  
    //State with h heaps, where the i-th heap starts with c[i] coins.  
    //A total of n players are in the game, numbered fron 0 to n-1  
    //and player 0 is the first to play  
    State (int h, const int c[], int n) {  
      A = new int[h];  
      heaps = h;  
      players = n;  
      playing = 0;  
  
      for (int i = 0; i < h; i++) {  
        A[i] = c[i];  
      }  
    };  
  
    ~State() {  
      delete [] A;  
    };  
  
    void next(const Move &move) throw(logic_error) {  
  
      if (A[move.getSource()] < move.getSourceCoins()) {  
        throw logic_error("Invalid move: Unable to move due to lack of coins in the heap");  
      }  
      else if (move.getSourceCoins() <= move.getTargetCoins()) {  
        throw logic_error("Invalid move: Cannot put more coins in target heap than those collected from the source heap");  
      }  
      else if (move.getSource() > heaps || move.getTarget() > heaps || move.getSource() < 0 || move.getTarget() < 0) {  
        throw logic_error("Game crashed. Please, restart.");  
      }  
      A[move.getSource()] -= move.getSourceCoins();  
      A[move.getTarget()] += move.getTargetCoins();  
      playing = (playing + 1) % players;  
    };  
  
    bool winning() const {  
      for (int i = 0; i < heaps; i++) {  
        if (A[i] != 0) return false;  
      }  
      return true;  
    };   
  
    int getHeaps() const {  
      return heaps;  
    };  
  
    int getCoins(int h) const throw(logic_error) {  
      if (h < 0 || h >= heaps) throw logic_error("GOLFALPHAYANKEE");  
      return *(A + h);  
    };  
  
    int getPlayers() const {  
      return players;  
    };  
  
    int getPlaying() const {  
      return playing;  
    };  
  
    friend ostream & operator << (ostream &out, const State &state) {  
      out << state.getCoins(0);  
  
      for (int i = 1; i < state.getHeaps(); i++) {  
        out << ", " << state.getCoins(i);  
      }  
  
      out << " with " << state.getPlaying();  
      out << "/" << state.getPlayers() << " playing next";  
      return out;  
    };  
  
  private:  
    int *A;  
    int players, heaps, playing;  
};