

#ifndef ECS_H_
#define ECS_H_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//#include "../leaker.h"


class Component;
class Entity;
class Manager;
class Game;
using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
  static ComponentID lastTypeID =0u;
  return lastTypeID++;
}

template <class T> inline ComponentID getComponentTypeID() noexcept
{
  static ComponentID typeID = getNewComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroup = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroup>;
using ComponentArray = std::array<Component* ,maxComponents>;

class Component
{
public:
  Entity* entity;

  int ID;

  virtual void init() {}
  virtual void update(){}
  virtual void draw() {}

  virtual ~Component(){
    //delete entity;
    std::cerr<<"Component object is destroy"<<std::endl;
  }

};

class Entity
{
private:
  bool active = true;
  int currentIndex=0;
  std::vector<Component*> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;
  GroupBitSet groupBitSet;

public:
  Manager* manager;

  Entity(Manager* mManager) : manager(mManager){}

  virtual ~Entity()
  {
    //delete manager;
    for(auto& comp : components)
      delete comp;
    std::cerr<<"Entity destroyed"<<std::endl;
  }
  void update()
  {
    for(auto* c: components) c->update();
  }
  void draw(){
    for(auto& c: components) c->draw();
  }

  bool zombie=false;
  bool player=false;
  void SetZombie(bool set){zombie=set;}
  void setPlayer(bool set){player=set;}
  bool isActive(){return active;}
  bool hasGroup(Group mGroup){return groupBitSet[mGroup];}
  void addGroup(Group mGroup);
  void delGroup(Group mGroup){groupBitSet[mGroup]=false;}
  void destroy(){active = false;}

  template <class T> bool hasComponent() const
  {
    return componentBitSet[getComponentTypeID<T>()];
  }

  template <class T, class... Targs>
  void addComponent(Targs&&... mArgs)
  {
    T* c = new T(Targs(mArgs)...);
    c-> entity = this;
    components.push_back(c);
    componentArray[getComponentTypeID<T>()]=c;
    componentBitSet[getComponentTypeID<T>()]=true;
    c->init();
  }

  template <class T> T& getComponent() const
  {
    T* asd= static_cast<T*>(componentArray[getComponentTypeID<T>()]);
    T& dsa=*asd;
    asd = NULL;
    delete asd;
    return dsa;
  }


};

class Manager
{
private:
  std::array<std::vector<Entity*>, maxGroup > groupedEntities;
  std::vector<Entity*> entities;
public:
  Game* m_game;

  void update()
  {
    for(auto* e: entities ) e->update();
  }
  void draw()
  {
    for(auto& e: entities) e->draw();
  }

  void refresh()
  {
    for(auto i(0u); i<maxGroup;i++)
    {
      auto& v(groupedEntities[i]);
      v.erase(std::remove_if(std::begin(v),std::end(v),[i](Entity* mEntity)
      {
        return !mEntity ->isActive() || !mEntity->hasGroup(i);
      }),
        std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities),std::end(entities),
      [](Entity* mEntity)
    {
      return !mEntity ->isActive();
    }),
      std::end(entities));
  }
  void addToGroup(Entity* entity, Group gr)
  {
    groupedEntities[gr].push_back(entity);
  }

  std::vector<Entity*>& getGroup(Group gr)
  {

    return static_cast<std::vector<Entity*> & >(groupedEntities[gr]);
  }

  Entity* addEntity()
  {
    Entity* e = new Entity(this);
    entities.push_back(e);
    return e;
  }

};




#endif //ECS_H_
