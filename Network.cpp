/*
Author: James Michael Crespo
File Name: Network.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Network' template class.
*/

#include "Network.hpp"

/**
  Default constructor.
  Initializes private variables to default initial values.
*/
template <class ItemType>
Network<ItemType>::Network()
{
  num_of_accounts_ = 0;
  network_feed_.clear();
}

/**
  Accessor function
  @return           : int -  the current size of the network (number of items in the array)
*/
template <class ItemType>
int Network<ItemType>::getSizeOfNetwork() const
{
  return num_of_accounts_;
}

/**
  @return           : bool -  true if the network is empty, false otherwise
*/
template <class ItemType>
bool Network<ItemType>::isEmpty() const
{
  return num_of_accounts_ == 0;
}

/**
  @param              : a POINTER to the item that will be added to the Network
  @return             : bool true if the item was successfully added, false otherwise
  @post               : stores a pointer to the item, if there is room. Item will be added only if
                        no other item in the network has the same username (usernames are considered unique)
                        Also, Account being added to the network will update it's private member to point to this network
*/
template <class ItemType>
bool Network<ItemType>::addAccount(ItemType *new_item)
{
  bool has_room = (num_of_accounts_ < 200);
  if (has_room)
  {
    for (int i = 0; i < num_of_accounts_; i++)
    {
      if (ptr_to_accounts_[i]->getUsername() == new_item->getUsername())
      {
        return false;
      }
    }
    ptr_to_accounts_[num_of_accounts_] = new_item;
    ptr_to_accounts_[num_of_accounts_]->setNetwork(this);
    num_of_accounts_++;
    return true;
  }
  return false;
}

/**
  Mutator function
  @param              : a POINTER to the item that will be removed from Network
  @return             : true if if the item was successfully removed, false otherwise
  @post               : updates the bag/network to remove the pointer, if a pointer to that item was found.
*/
template <class ItemType>
bool Network<ItemType>::removeAccount(const ItemType *old_item)
{
  int found_index = getIndexOf(old_item->getUsername());
  bool can_remove = !isEmpty() && (found_index > -1);
  if (can_remove)
  {
    num_of_accounts_--;
    ptr_to_accounts_[found_index] = ptr_to_accounts_[num_of_accounts_];
  }
  return can_remove;
}

/**
  Mutator function
  @post               : Empties the bag/network
*/
template <class ItemType>
void Network<ItemType>::clear()
{
  for (int i = 0; i < 200; i++)
  {
    ptr_to_accounts_[i] = nullptr;
  }
  network_feed_.clear();
  num_of_accounts_ = 0;
}

/**
  @param              : a POINTER to the item to find
  @return             : true if the item was successfully found, false otherwise
*/
template <class ItemType>
bool Network<ItemType>::containsAccount(const ItemType *item) const
{
  return getIndexOf(item->getUsername()) > -1;
}

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
template <class ItemType>
void Network<ItemType>::populateNetwork(std::string text_file)
{
  std::string line;
  std::string space = " ";
  std::regex format(".+[ ].+");
  std::ifstream my_file(text_file);
  if (my_file.is_open())
  {
    while (getline(my_file, line))
    {
      if (std::regex_match(line, format) && line != ";")
      {
        int space_pos = line.find(space);
        std::string username = line.substr(0, space_pos);
        std::string password = line.substr(space_pos + 1, line.length());
        ItemType *ptr_account = new ItemType(username, password);
        addAccount(ptr_account);
      }
      else if (!std::regex_match(line, format) && line == ";")
      {
        my_file.close();
      }
      else
      {
        my_file.close();
        std::cout << "Improper Format" << std::endl;
      }
    }
  }
}

/**
  Mutator function
  @param              : a reference to another Network
  @post               : Removes from the Network any items that also appear in the other Network.
*/
template <class ItemType>
void Network<ItemType>::operator-=(Network<ItemType> &item)
{
  for (int i = 0; i < num_of_accounts_; i++)
  {
    for (int j = 0; j < item.getSizeOfNetwork(); j++)
    {
      if (item.getIndexOf(ptr_to_accounts_[i]->getUsername()) > -1)
      {
        removeAccount(ptr_to_accounts_[i]);
      }
    }
  }
}

/**
  Accessor function
  @param              : a reference to the item whose feed will be displayed
  @post               : prints the feed of the given account by checking who they are following
*/
template <class ItemType>
void Network<ItemType>::printFeedForAccount(const ItemType &item)
{
  std::vector<std::string> following = item.viewFollowing(); // create vector of all user name this account follows.
  Node<Post *> *temp = network_feed_.getHeadPtr();           // assign head ptr of linkedlist to temp ptr
  while (temp != nullptr)
  {
    for (int i = 0; i < following.size(); i++) //
    {
      if (following[i] == temp->getItem()->getUsername())
      {
        temp->getItem()->displayPost();
      }
    }
    temp = temp->getNext();
  }
}

/**
  @param              : a reference to an item (account) and the username of the account it wants to follow
  @return             : true if the item was authorized to follow, false otherwise
  @post               : the referenced Account follows another account with the username
                        specified by the second argument if they both exist in the network
*/
template <class ItemType>
bool Network<ItemType>::authenticateFollow(ItemType &account, std::string username)
{
  if (getIndexOf(account.getUsername()) > -1 && getIndexOf(username) > -1)
  {
    account.followAccount(username);
    return true;
  }
  return false;
}

/**
  Mutator function
  @param              : a const Post pointer to item
  @return             : returns true if the Post was successfully added to the feed, false otherwise
  @post               : Adds the post to its feed only if the Post was created by an Account in this Network.
*/
template <class ItemType>
bool Network<ItemType>::addToFeed(Post *const post_ptr)
{
  if (getIndexOf(post_ptr->getUsername()) > -1) // check post_ptr's account to see if affiliated with current network
  {
    network_feed_.insert(post_ptr, 0); // add the post to the front of the network's linkedlist
    return true;
  }
  return false;
}

/**
  @param              : A string (word or phrase, case-sensitive) passed by reference
  @return             : The number of items removed from the list
  @post               : Any Post that contains the provided word or phrase in it's title, body or both
                        is removed from the Network's `network_feed_` as well as the Account's `posts_`.
*/
template <class ItemType>
int Network<ItemType>::removeIfContains(const std::string &keyword)
{
  Node<Post *> *temp = network_feed_.getHeadPtr();
  int remove_count = 0;
  while (temp != nullptr)
  {
    size_t found_title = temp->getItem()->getTitle().find(keyword);
    size_t found_body = temp->getItem()->getBody().find(keyword);
    if (found_title != std::string::npos || found_body != std::string::npos)
    {
      // remove post from Network's LinkedList
      network_feed_.remove(network_feed_.getIndexOf(temp->getItem()));
      // remove post from Account's LinkedList
      ItemType *temp_account = ptr_to_accounts_[getIndexOf(temp->getItem()->getUsername())];
      int post_pos_in_account = temp_account->getPosts().getIndexOf(temp->getItem());
      temp_account->getPosts().remove(post_pos_in_account);
      // increment counter of items removed
      remove_count++;
    }
    temp = temp->getNext();
  }
  return remove_count;
}

/**
  @return             : returns the Network's LinkedList 'network_feed_'
*/
template <class ItemType>
LinkedList<Post *> Network<ItemType>::getNetworkFeed() const
{
  return network_feed_;
}

// ********* PRIVATE METHODS **************//

/**
  private function
  @param              : the username of item we want the index of
  @return             : the index of the item, -1 if the account is not found
*/
template <class ItemType>
int Network<ItemType>::getIndexOf(const std::string &username) const
{
  bool found = false;
  int result = -1;
  int search_index = 0;

  while (!found && (search_index < num_of_accounts_))
  {
    if (ptr_to_accounts_[search_index]->getUsername() == username)
    {
      found = true;
      result = search_index;
    }
    else
    {
      search_index++;
    }
  }
  return result;
}