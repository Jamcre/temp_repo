/*
Author: James Michael Crespo
File Name: Account.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Account' class.
*/

#include "Account.hpp"

/**
    Default constructor.
    Sets the username and password of the Account to an empty string
    Sets the vector of posts to an empty vector
*/
Account::Account()
{
    setUsername("");
    setPassword("");
    posts_.clear();
}

/**
    Parameterized constructor.
    @param username  : username of the Account
    @param password  : password of the Account
    Sets the username and password of the Account to what was passed by the user
    Sets the vector of posts to an empty vector
*/
Account::Account(std::string username, std::string password)
{
    setUsername(username);
    setPassword(password);
    posts_.clear();
}

/**
    Mutator Function
    @param username  : reference to the username of the Account
*/
void Account::setUsername(const std::string &username)
{
    username_ = username;
}

/**
    Accessor Function
    @return the username of the Account
*/
std::string Account::getUsername() const
{
    return username_;
}

/**
    Mutator Function
    @param password  : reference to the password of the Account
*/
void Account::setPassword(const std::string &password)
{
    password_ = password;
}

/**
    Accessor Function
    @return the password of the Account
*/
std::string Account::getPassword() const
{
    return password_;
}

/**
    @param post_ptr  : const pointer to a Post object
    @post            : adds post to the front of Account's linkedlist, and if account is part of a network
                       adds post to the front of Network's linkedlist
    @return          : will return true if the Post does not have an empty title or body, and the
                       Post is successfully added to the account linkedlist (and network's linkedlist if possible)
*/
bool Account::addPost(Post *const post_ptr)
{
    if (post_ptr->getTitle() != "" && post_ptr->getBody() != "") // check if post has title and body
    {
        posts_.insert(post_ptr, 0);      // add the post to the front of the account's linkedlist
        if (pointed_network_ != nullptr) // check if account is affiliated with a network
        {
            pointed_network_->addToFeed(post_ptr); // add post to affiliated network's linked list
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
    @post            : Prints the linkedlist of Posts using their display function
*/
void Account::viewPosts() const
{
    Node<Post *> *temp = posts_.getHeadPtr(); // assign head ptr of linkedlist to temp ptr
    while (temp != nullptr)                   // condition to loop through linkedlist until nullptr is reached. (indicates end of linked list)
    {
        temp->getItem()->displayPost(); // access post_ptr in node, then access displayPost through post_ptr
        temp = temp->getNext();         // go to next node of linkedlist
    }
}

/**
    Accessor function
    @return          :   the pointer to the Network the account is in
*/
Network<Account> *Account::getNetwork() const
{
    return pointed_network_;
}

/**
    Mutator function
    @param           :   a pointer to a Network
    @post            :   sets the account's pointer private member to point to the input Network
*/
void Account::setNetwork(Network<Account> *ptr_to_network)
{
    pointed_network_ = ptr_to_network;
}

/**
    @param           :   the username of the Account to follow
    @return          :   true if the account was successfully able to follow, false otherwise
    @post            :   adds the username to the vector of following accounts only if
                         it is affiliated to a Network AND it is not already following an account
                         with the same username.
*/
bool Account::followAccount(const std::string username)
{
    if (usernames_following_.size() == 0 && pointed_network_ != nullptr)
    {
        usernames_following_.push_back(username);
        return true;
    }
    else if (usernames_following_.size() > 0 && pointed_network_ != nullptr)
    {
        for (int i = 0; i < usernames_following_.size(); i++)
        {
            if (usernames_following_[i] == username)
            {
                return false;
            }
        }
        usernames_following_.push_back(username);
        return true;
    }
    else
    {
        return false;
    }
}

/**
    Accessor function
    @return          :   the vector of usernames the Account is following
*/
std::vector<std::string> Account::viewFollowing() const
{
    return usernames_following_;
}

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
void Account::updatePost(Post *post, std::string new_title, std::string new_body)
{
    if (new_title != "")
        post->setTitle(new_title);
    if (new_body != "")
        post->setBody(new_body);
    post->getTimeStamp();
    posts_.moveItemToTop(post);
    pointed_network_->getNetworkFeed().moveItemToTop(post);
}

/**
    @param           :   Pointer to a Post object
    @return          :   True, if the Post was successfully found and removed. False otherwise
    @post            :   This function will remove the given Post from its list as well as from the Network's feed.
                         Returns True if successfully removed, False if not. Afterwards, tell the Network to remove
                         the Post as well from its feed.
*/
bool Account::removePost(Post *post)
{
    Node<Post *> *temp = posts_.getHeadPtr();
    while (temp != nullptr)
    {
        if (temp->getItem() == post)
        {
            // remove item from 'Account' LinkedList
            posts_.remove(posts_.getIndexOf(post));
            // remove item from 'Network' LinkedList
            pointed_network_->getNetworkFeed().remove(pointed_network_->getNetworkFeed().getIndexOf(post));
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

/**
    Accessor function
    @return          :   the Account's linkedlist 'posts_'
*/
LinkedList<Post *> Account::getPosts() const
{
    return posts_;
}