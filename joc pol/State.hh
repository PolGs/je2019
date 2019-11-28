#ifndef State_hh
#define State_hh


#include "Structs.hh"


/*! \file
 * Contains a class to store the current state of a game.
 */


/**
 * Stores the game state.
 */
class State {

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  int round_;
  vector< vector<Cell> > grid_;
  vector<Unit> unit_;
  vector<vector<int>> dwarves_;
  vector<vector<int>> wizards_;
  vector<int> orcs_;
  vector<int> trolls_;
  int balrog_id_;
  vector<int> nb_cells_;      // current
  vector<int> nb_treasures_;  // accumulated
  vector<double> cpu_status_; // -1 -> dead, 0..1 -> % of cpu time limit

  /**
   * Returns whether id is a valid unit identifier.
   */
  inline bool unit_ok (int id) const {
    return id >= 0 and id < nb_units()
           and (unit_[id].health > 0 or unit_[id].type == Balrog);
  }

public:

  /**
   * Returns the current round.
   */
  inline int round () const {
    return round_;
  }

  /**
   * Returns a copy of the cell at p.
   */
  inline Cell cell (Pos p) const {
    if (p.i < 0 or p.i >= (int)grid_.size()
        or p.j < 0 or p.j >= (int)grid_[p.i].size()) {
      cerr << "warning: cell requested for position " << p << endl;
      return Cell();
    }
    return grid_[p.i][p.j];
  }

  /**
   * Returns a copy of the cell at (i, j).
   */
  inline Cell cell (int i, int j) const {
    return cell(Pos(i, j));
  }

  /**
   * Returns the total number of units in the game.
   */
  inline int nb_units () const {
    return unit_.size();
  }

  /**
   * Returns the information of the unit with identifier id.
   */
  inline Unit unit (int id) const {
    if (not unit_ok(id)) {
      cerr << "warning: unit requested for identifier " << id << endl;
      return Unit();
    }
    return unit_[id];
  }

  /**
   * Returns the current number of cells owned by a player.
   */
  inline int nb_cells (int pl) const {
    if (pl < 0 or pl >= (int)nb_cells_.size()) {
      cerr << "warning: num_cells requested for player " << pl << endl;
      return -1;
    }
    return nb_cells_[pl];
  }

  /**
   * Returns the number of treasures already accumulated by a player.
   */
  inline int nb_treasures (int pl) const {
    if (pl < 0 or pl >= (int)nb_treasures_.size()) {
      cerr << "warning: treasures requested for player " << pl << endl;
      return -1;
    }
    return nb_treasures_[pl];
  }

  /**
   * Returns the percentage of cpu time used up to the last round, in the
   * range [0.0 ... 1.0] or a value lesser than 0 if this player is dead.
   * Note that this is only accessible if secgame() is true.
   */
  inline double status (int pl) const {
    if (pl < 0 or pl >= (int)cpu_status_.size()) {
      cerr << "warning: status requested for player " << pl << endl;
      return -1;
    }
    return cpu_status_[pl];
  }

  /**
   * Returns the ids of all the dwarves of a player.
   */
  inline vector<int> dwarves (int pl) const {
    if (pl < 0 or pl >= (int)dwarves_.size()) {
      cerr << "warning: dwarves requested for player " << pl << endl;
      return vector<int>();
    }
    return dwarves_[pl];
  }

  /**
   * Returns the ids of all the wizards of a player.
   */
  inline vector<int> wizards (int pl) const {
    if (pl < 0 or pl >= (int)wizards_.size()) {
      cerr << "warning: wizards requested for player " << pl << endl;
      return vector<int>();
    }
    return wizards_[pl];
  }

  /**
   * Returns the ids of all the orcs currently alive.
   */
  inline vector<int> orcs () const {
    return orcs_;
  }

  /**
   * Returns the ids of all the trolls.
   */
  inline vector<int> trolls () const {
    return trolls_;
  }

  /**
   * Returns the id of the Balrog.
   */
  inline int balrog_id () const {
    return balrog_id_;
  }

};


#endif
