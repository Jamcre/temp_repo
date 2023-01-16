/*
Author: James Michael Crespo
File Name: Account.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'Account' class.
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Post.hpp"
#include "Network.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

class Account
{

public:
  /**
  Default constructor.
  Sets the username and password of the Account to an empty string
  Sets the vector of posts to an empty vector
  */
  Account();

  /**
  Parameterized constructor.
  @param username  : username of the Account
  @param password  : password of the Account
  Sets the username and password of the Account to what was passed by the user
  Sets the vector of posts to an empty vector
  */
  Account(std::string username, std::string password);

  /**
  Mutator Function
  @param username  : reference to the username of the Account
  */
  void setUsername(const std::string &username);

  /**
  Accessor Function
  @return the username of the Account
  */
  std::string getUsername() const;

  /**
  Mutator Function
  @param password  : reference to the password of the Account
  */
  void setPassword(const std::string &password);

  /**
  Accessor Function
  @return the password of the Account
  */
  std::string getPassword() const;

  /**
  @param post_ptr  : const pointer to a Post object
  @post            : adds post to the front of Account's linkedlist, and if account is part of a network
                     adds post to the front of Network's linkedlist
  @return          : will return true if the Post does not have an empty title or body, and the
                     Post is successfully added to the account linkedlist (and network's linkedlist if possible)
  */
  bool addPost(Post *const post_ptr);

  /**
  @post            : Prints the linkedlist of Posts using their display function
  */
  void viewPosts() const;

  /**
  Accessor function
  @return          :   the pointer to the Network the account is in
  */
  Network<Account> *getNetwork() const;

  /**
  Mutator function
  @param           :   a pointer to a Network
  @post            :   sets the account's pointer private member to point to the input Network
  */
  void setNetwork(Network<Account> *ptr_to_network);

  /**
  @param           :   the username of the Account to follow
  @return          :   true if the account was successfully able to follow, false otherwise
  @post            :   adds the username to the vector of following accounts only if
                        it is affiliated to a Network AND it is not already following an account
                        with the same username.
  */
  bool followAccount(const std::string username);

  /**
  Accessor function
  @return          :   the vector of usernames the Account is following
  */
  std::vector<std::string> viewFollowing() const;

  /**
  @param           :   Pointer to a Post object
  @param           :   The new title of the Post (or empty string if you don't want to change it)
  @param           :   The new body of the Post (or empty string if you don't want to change it)
  @post            :   This function will take the Post and given the new title and body,
                       update the Posts title and body as appropriate. It will also update the `timestamp_`
                       to the current time of the update. This function should then update the location of the
                       Post in its list of `posts_` to the front of the list as well as utilizing its
                       Network pointer to do the same in the `network_feed_`.
  */
  void updatePost(Post *post, std::string new_title, std::string new_body);

  /**
  @param           :   Pointer to a Post object
  @return          :   True, if the Post was successfully found and removed. False otherwise
  @post            :   This function will remove the given Post from its list as well as from the Network's feed.
                       Returns True if successfully removed, False if not. Afterwards, tell the Network to remove
                       the Post as well from its feed.
  */
  bool removePost(Post *post);

  /**
  Accessor function
  @return          :   the Account's linkedlist 'posts_'
  */
  LinkedList<Post *> getPosts() const;

private:
  std::string username_;
  std::string password_;
  LinkedList<Post *> posts_;
  std::vector<std::string> usernames_following_;
  Network<Account> *pointed_network_ = nullptr;
};

#endif