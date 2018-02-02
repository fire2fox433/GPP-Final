#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <initializer_list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "characters.h"
#include "map.h"
#include "platform.h"
#include "constants.h"

class BehaviourTree
{
	public:
		class Node {  // This class represents each node in the behaviour tree.
			public:
				virtual bool run() = 0;
		};
		
		class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
			private:
				std::vector<Node*> children;
			public:
				const std::vector<Node*>& getChildren() const {return children;}
				void addChild (Node* child) {children.emplace_back(child);}
				void addChildren (std::initializer_list<Node*>&& newChildren) {for (Node* child : newChildren) addChild(child);}
				template <typename CONTAINER>
				void addChildren (const CONTAINER& newChildren) {for (Node* child : newChildren) addChild(child);}
			protected:
				std::vector<Node*> childrenShuffled() const {std::vector<Node*> temp = children;  std::random_shuffle (temp.begin(), temp.end());  return temp;}
		};
		

		//class Selector : public CompositeNode {
		//	public:
		//		virtual bool run() override {
		//			for (Node* child : getChildren()) {  // The generic Selector implementation
		//				if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
		//					return true;
		//			}
		//			return false;  // All children failed so the entire run() operation fails.
		//		}

		//};


		class Sequence : public CompositeNode {
			public:
				virtual bool run() override {
					for (Node* child : getChildren()) {  // The generic Sequence implementation.
						if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
							return false;
					}
					return true;  // All children suceeded, so the entire run() operation succeeds.
				}
		};


		class Root : public Node {
			private:
				Node* child;
				friend class BehaviourTree;
				void setChild (Node* newChild) {child = newChild;}
				virtual bool run() override {return child->run();}
		};


		//Types of Behaviors (Escape (Branch into Side of Walls and general running away) , Fighting, Picking up Items)
		class MainSelector : public CompositeNode {
		private:
			Characters* chars;
			std::vector<Platform*> platforms;
		public:
			MainSelector(Characters* chars, std::vector<Platform*> platforms) { this->chars = chars; this->platforms = platforms; }
			virtual bool run() override {
				bool platformBelow = false;
				for (std::vector<int>::size_type i = 0; i != platforms.size(); i++) {
					if ((chars->getX() + charactersNS::WIDTH/2 * chars->getScale() >= platforms[i]->getY()) && (chars->getX() + charactersNS::WIDTH/2 * chars->getScale() <= platforms[i]->getY() + platformNS::WIDTH * platforms[i]->getScale()))
					{
						platformBelow = true;
					}
				}
				if (platformBelow == true)
				{
					return getChildren()[1]->run();
				}
				else if (chars->getHealthComponent()->getPerc() > 100)
				{
					return getChildren()[0]->run();
				}
			}
		};

		class jumpToNearestPlatform : public Node {
		private:
			Characters* chars;
			std::vector<Platform*> platforms;
		public:
			jumpToNearestPlatform(Characters* chars, std::vector<Platform*> platforms) { this->chars = chars; this->platforms = platforms; }
			virtual bool run() override {
				int indexOfMostPreferrablePlatform;
				float distanceToClosestPlatform = GAME_WIDTH * GAME_HEIGHT;
				float currentCharX = chars->getX() + charactersNS::WIDTH/2 * chars->getScale();
				float currentCharY = chars->getY() + charactersNS::HEIGHT / 2 * chars->getScale();
				for (std::vector<int>::size_type i = 0; i != platforms.size(); i++) {
					float disX = currentCharX - (platforms[i]->getX() + platformNS::WIDTH * platforms[i]->getScale() / 2 );
					if (disX < 0)
						disX *= -1;
					float disY = currentCharY - (platforms[i]->getY() + platformNS::HEIGHT * platforms[i]->getScale() / 2);
					if (disY < 0)
						disX *= -1;
					float totalDist = sqrt(disX * disX + disY * disY);
					if (totalDist < distanceToClosestPlatform)
					{
						distanceToClosestPlatform = totalDist;
					}
				}
				if (distanceToClosestPlatform > 0)
				{
					chars->moveRight();
				}
				else if (distanceToClosestPlatform < 0)
				{
					chars->moveLeft();
				}
				else
				{

				}

				if (!(chars->getJumpCounter() >= 2) && chars->getMoveComponent()->getVelocity().y >= 0)
				{
					chars->jump();
				}
			}
		};

		class escapePlayers : public Node {
		private:
			Characters * chars;
			std::vector<Platform*> platforms;
			std::vector<Characters*> characters;
		public:
			escapePlayers(Characters* chars, std::vector<Platform*> platforms) { this->chars = chars; this->platforms = platforms; }
			virtual bool run() override {
				Platform* targetedPlatform;
				float highestTotalDis = 0;
				for (std::vector<int>::size_type i = 0; i != platforms.size(); i++) {
					float totalDistance = 0;
					for (std::vector<int>::size_type z = 0; z != characters.size(); z++)
					{
						float xDis = characters[z]->getX() - platforms[i]->getX();
						float yDis = characters[z]->getY() - platforms[i]->getY();
						if (xDis < 0)
							xDis *= -1;
						if (yDis < 0)
							yDis *= -1;
						totalDistance += sqrt(xDis * xDis + yDis * yDis);
					}
					if (targetedPlatform == NULL)
					{
						targetedPlatform = platforms[i];
						highestTotalDis = totalDistance;
					}
					else
					{
						if (highestTotalDis < totalDistance)
						{
							targetedPlatform = platforms[i];
							highestTotalDis = totalDistance;
						}
					}
				}
			}
		};

	private:
		Root* root;
	public:
		BehaviourTree() : root(new Root) {}
		void setRootChild (Node* rootChild) const {root->setChild (rootChild);}
		bool run() const {return root->run();}
};