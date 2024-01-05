/*
 * characters.h
 *	Title: The good, the bad and the zombie
 *	Programming Techniques Assignment #1
 *
 *  Created on: Apr 4, 2016
 *      Author: Marios Papachristou (el15101)
 *      email: el15101@mail.ntua.gr / papachristoumarios@gmail.com
 *      github: papachristoumarios
 *
 *  Description:
 *  This is the header file for the World. It contains some basic class and type definitions as
 *  well as member declarations for each of the classes respectively
 *
 *	Inheritance Diagram:
 *	Character > Good, Bad, Zombie (publicly inherited)
 *  and Person class defines a bijection with Character
 *  
 */

#include <list>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <typeinfo>
#include <ctime>
#include <cassert>
#include <random>
#include <vector>

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

//constant definitions
#define TEAMS 3
#define round ROUND
#define MAX_ROUND 100

//some prototype-style classdefs
class Character;
class Good;
class Bad;
class Zombie;
class World;
class Person;

// This enum contains the three base IDs for the World: GOOD, BAD and ZOMBIE
enum  AVAIL_IDS {GOOD, BAD, ZOMBIE};

//Type definitions for PlayerList and ScoreList
typedef std::list<Person*> PlayerList;
typedef unsigned int ScoreList [TEAMS];
typedef enum AVAIL_IDS PlayerType;

class Person {
/*
 * This is a wrapper class for Character that defines a bijecive (1-1) relation between a Person and a Character
 */
	private:
		Character* has_character;
		/*
		 * Points to associated Character
		 */
		unsigned int* hit_points; 
		bool is_dead;
	public:
		//public members of Person class contain wrapper methods for mutating the associated Character
		Character* hit(Character*);
		Person* hit(Person*);
		Person(Character *);
		Person(PlayerType,bool);
		int get_hp();
		void set_hp(int);
		~Person();
		Character* get_character();
		void set_character(Character*);
		PlayerType get_id();
		Character* convert(PlayerType);
		friend Person* convert_to(Person*, PlayerType);
		void lower_hp();
		void heal();
		void print_data();
		Character* get_attached_character();
		void set_attached_character(Character*);
};

class Character {
	/**
	 * This is the base character class
	 * One can create a character this way and can be used as a superclass for other character-type
	 * daughter classes. A Character object has an id and hit points (HP)
	 * This base class supports some basic functionality for our characters.
	 * A character can be lower_hpd, healed and attack other character as well as be convert_toed to other type.
	 */
private:
	Person* is_attached_to;
	void set_id(PlayerType id);
	/*
	 * Modify the ID of a character
	 */
protected:
	PlayerType character_id;
	/*
	 * Player id is an element of AVAIL_IDS enum
	 */
	void lower_hp(int);
	/*
	 * lower_hps the current character by a certain amount (default is 10 HP)
	 */
	unsigned int hit_points;

	/*
	 * Creates a new character given a specified id (default is ZOMBIE)
	 */
public:
	Character (PlayerType id);
	void set_hp(int hp);
	/*
	 * Set HP (health points)
	 */

	static char* get_character_type(Person&);
	virtual Character* attack(Character&);
	/*
	 * Virtual method for attacking another Character object (may convert_to it to other type
	 */
	 virtual Person* attack(Person*);
	 /*
	  * Same as above but used to attack a Person
	  */ 
	virtual int get_hp();
	/*
	 * Returns HP of current character
	 */
	virtual int get_id();
	/*
	 * Returns ID of current character
	 */
	virtual char* get_ct();
	/*
	 * Returns type as type_info object 
	 */
	void print_data();
	/*
	 * Prints the data of the current character (ID and HP)
	 */
	virtual void heal();
	/*
	 * heals current character
	 */
	virtual ~Character();
	/*
	 * Character destructor
	 */
	//friend functions and classes
		Character& convert(PlayerType T);
	/*
	 * convert_tos current character to other player type. Modifies "this" pointer.
	 */
	friend Character* convert_to(Character*, PlayerType);
	friend class Zombie;
	friend class Good;
	friend class Bad;
	friend class Person;
	friend class World;
};

//characters
class Good : public Character {
	/**
	 * This class inherits from Character and is used to create Good Characters
	 */

public:
	operator Zombie(); //cast operator for conversion to Zombie
	Good(); //default constructor for good
	Good(Character&); //copy constructor with Character& argument
	~Good();
	//Character* attack(Character&);
	/*
	 * attack method implemented for Good characters. That means that:
	 * When Good attacks Zombie it can heal it with a probability 20% and convert_to it either to Good (with probability 40%) or Bad (with probability 60%)
	 * It lower_hps Bad characters.
	 * Returns pointer to Character
	 */
	 Person* attack(Person*);
};

class Bad : public Character {
	/**
	 * This class inherits from Character and is used to create Bad Characters
	 */
public:
	operator Zombie(); //cast operator for conversion to Zombie
	Bad(); //default constructor for Bad
	Bad(Character&); //copy constructor with Character& argument
	~Bad();
	//Character* attack(Character&);
	/*
	 * attack method implemented for Bad. It just lower_hps other player types by 10 HP.
	 * Returns pointer to Character
	 */
 	 Person* attack(Person*);
};

class Zombie : public Character {
	/**
	 * This class inherits from Character and is used to create Zombies!
	 */
public:
	operator Good(); //cast operator for conversion to Good
	operator Bad(); //cast operator for conversion to Bad
	Zombie(); //default constructor for Zombie
	Zombie(Character&); //copy constructor with Character& argument
	~Zombie();
	//Character* attack(Character&);
	/*
	 * attack method implemented for Zombie. It lower_hps other player types and has a 10% chance of convert_toing them to Zombies.
	 */
 	 Person* attack(Person&);
 	 Person* attack(Person*);
};

//exceptions
class UnrecognizedCharacterException : public std::exception {
	const char* what() { return "Cannot recognize this type of character";}
}; //thrown when invalid player type is spawned
class UnrecognizedConversionException : public std::exception {
	const char* what() { return "Cannot perform this type of conversion"; }
}; //thrown when conversion cannot be completed


//World
class  World {
	/**
	 * This is the class that is used to define a World in which some characters are arranged at a cyclic linked list and each
	 * character hits the next one and lower_hps it in case it is of another type. The World ends either when there's only one team left
	 * or after 100 rounds.
	 */
private:
	PlayerList players; //A list that contains Pointers to Person objects and holds the players of the game
	ScoreList scores; //An array that keeps the scores 
	bool update_scores(); //A function to update scores and declare winners or no winners
	unsigned int round; 
	void kill_player(int pos);
	void round_cleanup();
public:
	World(PlayerList); 
	World(unsigned int);
	virtual ~World(); //virtual destructor of class World. It destroys the items on the list
	void play_round(); //Plays one round
	void play_world(); //Plays a whole game (world)
	void display_world(); //Displays world status
	void display_scores(); //Displays each team's score
	//bool update_scores(); 
	static World Default(); //Creates a world with 10 players
	static Character* spawn_character(PlayerType); //factory fashioned spawning for Character
	Person* spawn_person(PlayerType); //factory-fashoned spawning for Person
};

#endif
