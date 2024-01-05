/*
 * characters.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: Marios Papachristou (el15101)
 *      email: el15101@mail.ntua.gr / papachristoumarios@gmail.com
 *      github: papachristoumarios
 *      For more info and documentation head over characters.h
 */

#include "characters.h"

using namespace std;

// Uniform int distribution
default_random_engine generator;
uniform_int_distribution<int> distribution(0,99); //TODO Use this generator
uniform_int_distribution<int> id_distribution(0,2);

//wrapper character class
Person::Person(Character *ch) {
	this->has_character = ch;
	this->hit_points = &(this->has_character->hit_points);
	this->is_dead = (this->has_character->hit_points <= 0);
	this->has_character->is_attached_to = this;
}

void Person::heal() {*hit_points = 100;}

Person::Person(PlayerType id, bool nothrow=true) {
	switch(id) {
		case GOOD:
			this->has_character = new Good(); break;
		case BAD:
			this->has_character = new Bad(); break;
		case ZOMBIE:
			this->has_character = new Zombie(); break;
		default:
			this->has_character = new Character(id); break;
			if (!nothrow) throw UnrecognizedCharacterException();
	};
	this->hit_points = &(this->has_character->hit_points);
	this->is_dead = (this->has_character->hit_points <= 0);
	this->has_character->is_attached_to = this;
}

Character* Person::hit(Character *p) { return this->has_character->attack(*p); }
Person* Person::hit(Person *p) { Person *q = this->has_character->attack(p); return q; };

int Person::get_hp() { return *(this->hit_points); }
void Person::set_hp(int hp) { *(this->hit_points) = hp; }

Character* Person::convert(PlayerType T) {
	this->has_character = convert_to(this->has_character, T);
	return this->has_character;
} 

void Person::print_data() {
	printf("%s-%d\n",this->has_character->get_ct() , *(this->hit_points));
}

Person::~Person() {delete this->has_character;}

Character* Person::get_character() { return has_character; };
void Person::set_character(Character *ch) { has_character = ch ; };

PlayerType Person::get_id() { return has_character->character_id; };

void Person::lower_hp() {
	*this->hit_points -= 10;
	this->is_dead = *(this->hit_points) <= 0; 
}

Character* Person::get_attached_character() {
	return this->has_character;
}

void Person::set_attached_character(Character *ch) {
	this->has_character = ch;
	this->is_dead = ch->get_hp() <= 0;
}

//constructor
Character::Character (PlayerType id = ZOMBIE) {
	character_id = id;
	hit_points = 100;
}

int Character::get_hp() {
	return hit_points;
}

int Character::get_id() {
	return character_id;
}

void Character::lower_hp(int amount = 10) {
	hit_points = hit_points - amount;
}

void Character::set_hp(int hp) {
	hit_points = hp;
}

void Character::heal() {
	hit_points = 100;
}

void Character::set_id(PlayerType id) {
	character_id = id;
}

Character::~Character() {
	//if (hit_points <= 0) printf("ouch!A %s was just killed\n", this->get_ct());
}

void Character::print_data(){
	printf("ID: %s HP: %d\n", this->get_ct() , hit_points);
}

char* Character::get_ct() {
	char *char_type = (char*) typeid(*this).name();
	return char_type + ( (int)char_type[0] >= 48 && (int)char_type[0] <= 57 ? 1 : 0 );
}

Character* Character::attack (Character& other) {
	other.lower_hp(); return &other;
}

char* Character::get_character_type(Person& p) {
	return (char*) typeid( *( p.get_character() )).name() + 1;
}

Person* Character::attack(Person *other) {
	Character *ch = other->get_character();
	ch = this->attack(*ch);
	other->set_character(ch);
	return other;
}

//constructors
Good::Good() : Character(GOOD) { }
Bad::Bad() : Character(BAD) { }
Zombie::Zombie() : Character(ZOMBIE) { }

Good::~Good() { if (this->hit_points <= 0) printf("Oh my God!\n"); }
Bad::~Bad() { if (this->hit_points <= 0) printf("I will never rule the World!\n"); }
Zombie::~Zombie() { if (this->hit_points <= 0) printf("Urrrrrgh!\n"); }

Good::Good(Character& ch)  {
	hit_points = ch.get_hp();
	character_id = GOOD;
}

Bad::Bad(Character& ch) {
	hit_points = ch.get_hp();
	character_id = BAD;
}

Zombie::Zombie(Character& ch) {
	hit_points = ch.get_hp();
	character_id = ZOMBIE;
}

//cast operators
Good::operator Zombie() {
	Character *z = convert_to(this, ZOMBIE);
	delete this; return *z;
}

Bad::operator Zombie() {
	Character *z = convert_to(this, ZOMBIE);
	delete this; return *z;
}

Zombie::operator Good() {
	Character *g = convert_to(this, GOOD);
	delete this; return *g;
}

Zombie::operator Bad() {
	Character *b = convert_to(this, BAD);
	delete this; return *b;
}

Person* Good::attack(Person* other) {
	int target_id = other->get_id();
	if (target_id == GOOD) return other;
	else if (target_id == BAD) { other->lower_hp(); return other; }
	
	else if (target_id == ZOMBIE) {
		
		if (distribution(generator) > 20) other->lower_hp();
		//if (rand() % 100 > 20) other->lower_hp();
		else {
			other->heal();
			if (distribution(generator) <= 40) other = convert_to(other , GOOD);
			else other = convert_to(other , BAD);
				other->lower_hp();
		}
	}
	return other;	
}

Person* Bad::attack(Person *other) {
	if (other->get_id() != BAD) other->lower_hp(); 
	return other;
}

Person* Zombie::attack(Person *other) {
	if (other->get_id() == ZOMBIE) return other;
	if (distribution(generator) <= 10) {
		Person *p = convert_to(other, ZOMBIE);
		p->lower_hp();
		return p;
	}
	other->lower_hp();
	return other;
}

Character* convert_to(Character *ch, PlayerType T) {
	Character *x;
	int y = ch->get_id();
	if (y == GOOD || y == BAD) {
			if (T != ZOMBIE) return ch;
			x = new Zombie();
	}
	else if (y == ZOMBIE) {
		if (!(T == GOOD || T == BAD)) return ch;
		if (T == GOOD) x = new Good();
		else if (T == BAD) x = new Bad();
		else throw UnrecognizedConversionException();
	}
	x->hit_points = ch-> hit_points;
	delete ch;
	return x;
}

Character& Character::convert(PlayerType T) {
	try {
		*this = *convert_to(this, T); //modifies this since every Character subclass occupies exactly the same memory blocks
		return *this;
	} catch (UnrecognizedConversionException &e) {
		return *this;
	}
}

Person* convert_to(Person *p, PlayerType T) {
	try {
	Character *temp = p->has_character;
	temp  = convert_to(temp, T); 
	p->has_character = temp;
	return p;
	}
	catch (exception& e) {
		throw UnrecognizedConversionException();
		return p;
	}
}

//World
World::World(unsigned int N=10) {
	round = 0;
	for (int i = 0; i < TEAMS; i++) scores[i] = 0;
	for (unsigned int i = 0; i < N; i++) {
		int tmp = id_distribution(generator);
		//int tmp = rand() % 3;
		players.push_back(new Person((PlayerType) (tmp)));
		scores[tmp]++;
	}
}

World::World(PlayerList init) {
	players = init;
	round = 0;
	for (int i = 0; i < TEAMS; i++) scores[i] = 0;
	for (PlayerList::iterator it = players.begin(); it != players.end(); ++it) {
		scores[ (int) ((*it)->get_id())]++;
	} 
}

void World::display_world() {
	printf("[");
	PlayerList::iterator it = players.begin();
	for (unsigned int i = 0; i < players.size(); i++) {
		Character *tmp = (*it)->get_character();
		if (tmp->get_hp() > 0) { 
			printf("%s-%d", tmp->get_ct() , tmp->get_hp() );
			if (i != players.size() - 1) printf(", ");
		}
		++it;
	}
	printf("]\n");
}

bool declare_dead(Person *p) {
	return p->get_hp() <= 0;
}

void World::play_round() {
	if (players.size() < 2) return;

	PlayerList::iterator it = players.begin();
	unsigned int k = 0;
	
	while (k < players.size() - 1) {
		int id1 = (*next(it))->get_id(); 
		
		if ( (*it)->get_hp() > 0) (*it)->hit(*(next(it)));
		else scores[(*it)->get_id()]--;
		
		int id2 = (*next(it))->get_id();
		
		if (id1 != id2) {
			scores[id1]--; scores[id2]++; //alter scores in case someone is converted
		}
		++it; ++k; 
	}
	//last player hits first player on the list
	int id1 = (*players.begin())->get_id();
	if (players.back()->get_hp() > 0) players.back()->hit(*(players.begin()));
	else scores[players.back()->get_id()]--;
	int id2 = (*players.begin())->get_id();
	if (id1 != id2) {scores[id1]--; scores[id2]++;; }
	//this->round_cleanup(); 
	players.remove_if(declare_dead);
	round++;
}

void World::display_scores() {
	printf("Goods: %d, Bads: %d, Zombies: %d\n", scores[(int)GOOD], scores[(int)BAD], scores[(int)ZOMBIE]);
}

bool World::update_scores() {
	if (round > MAX_ROUND) {
		printf("No-one Wins\n");
		return false;
	}
	int n = 0; int w = -1;
	for (int i = 0; i < TEAMS; i++) {
		if (scores[i] == 0) n++;
		else w = i;
	}
	if (n == TEAMS - 1 && w != -1) {
		printf("Team %s wins!\n",  (*players.begin())->get_character()->get_ct());
		return false;
	}
	return true;
}

void World::play_world() {
	display_world();
	while(update_scores())  {
		 play_round();
		 display_world();
	}
}

World::~World() {
	for (Person* it: players) {
		Person *tmp = it;
		it = NULL;
		delete tmp;
	}
	printf("World destroyed successfully\n");
}

Person* World::spawn_person(PlayerType T) {
	//we could perhaps made some assertions here if we were real programmers
	Person *p = new Person(T);
	players.push_back(p);
	return p;
}

int main(void) {
	//srand(time(NULL));
	int N;
	printf("Enter number of players: ");
	scanf("%d", &N);
	//assert(N > 0);
	if (N > 0) {
	World *world = new World((unsigned int) N);
	world->play_world();
	delete world;
	}
	
	else printf("Please enter positive number of players!\nGoodbye!\n");
}
