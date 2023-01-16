/*
Author: James Michael Crespo
File Name: Network.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'Network' template class.
*/

#ifndef NETWORK_H_
#define NETWORK_H_

#include "Post.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

template <class ItemType>
class Network
{
public:
  /**
    Default constructor.
    Initializes private variables to default initial values.
  */
  Network();

  /**
    Accessor function
    @return           : int -  the current size of the network (number of items in the array)
  */
  int getSizeOfNetwork() const;

  /**
    @return           : bool -  true if the bag is empty, false otherwise
  */
  bool isEmpty() const;

  /**
  @param              : a POINTER to the item that will be added to the Network
  @return             : bool true if the item was successfully added, false otherwise
  @post               : stores a pointer to the item, if there is room. Item will be added only if
                        no other item in the network has the same username (usernames are considered unique)
                        Also, Account being added to the network will update it's private member to point to this network
  */
  bool addAccount(ItemType *new_item);

  /**
  Mutator function
  @param              : a POINTER to the item that will be removed from Network
  @return             : true if if the item was successfully removed, false otherwise
  @post               : updates the bag/network to remove the pointer, if a pointer to that item was found.
  */
  bool removeAccount(const ItemType *old_item);

  /**
  Mutator function
  @post               : Empties the bag/network
  */
  void clear();

  /**
  @param              : a POINTER to the item to find
  @return             : true if the item was successfully found, false otherwise
  */
  bool containsAccount(const ItemType *item) const;

  /**
  Mutator function
  @param              : the name of an input file
  @pre                : The format of the text file is as follows:
                        username password
                        username password
                        ;
                        where ';' signals the end of the file. Check the provided example (accounts.txt).
  @post               : Reads every line in the input file, creates an Account from that information and
                        adds the Account to the network. If a line of input is missing some required information,
                        it prints out "Improper Format" and terminates.
  */
  void populateNetwork(const std::string text_file);

  /**
  Mutator function
  @param              : a reference to another Network
  @post               : Removes from the Network any items that also appear in the other Network.
  */
  void operator-=(Network<ItemType> &item);

  /**
  Accessor function
  @param              : a reference to the item whose feed will be displayed
  @post               : prints the feed of the given account by checking who they are following
  */
  void printFeedForAccount(const ItemType &item);

  /**
  @param              : a reference to an item (account) and the username of the account it wants to follow
  @return             : true if the item was authorized to follow, false otherwise
  @post               : the referenced Account follows another account with the username
                        specified by the second argument if they both exist in the network
  */
  bool authenticateFollow(ItemType &account, std::string username);

  /**
  Mutator function
  @param              : a const Post pointer to item
  @return             : returns true if the Post was successfully added to the feed, false otherwise
  @post               : Adds the post to its feed only if the Post was created by an Account in this Network.
  */
  bool addToFeed(Post *const post_ptr);

  /**
  @param              : A string (word or phrase, case-sensitive) passed by reference
  @return             : The number of items removed from the list
  @post               : Any Post that contains the provided word or phrase in it's title, body or both
                        is removed from the Network's `network_feed_` as well as the Account's `posts_`.
  */
  int removeIfContains(const std::string &keyword);

  /**
  @return             : returns the Network's LinkedList 'network_feed_'
  */
  LinkedList<Post *> getNetworkFeed() const;

private:
  /**
  private function
  @param              : the username of item we want the index of
  @return             : the index of the item, -1 if the account is not found
  */
  int getIndexOf(const std::string &username) const;

  int num_of_accounts_;
  ItemType *ptr_to_accounts_[200];
  LinkedList<Post *> network_feed_;
};

#include "Network.cpp"
#endif