/*
Author: James Michael Crespo
File Name: Post.cpp
Date of Creation: 09/13/2022

Description: This file contains the implementation of the 'Post' class.
*/

#include "Post.hpp"

/**
    Parameterized constructor.
    @param title  : The title of the post
    @param body   : The body content of the post
    Sets the title and body of the Post to what was passed by the user
    Will also generate the current time and store it
*/
Post::Post(std::string title, std::string body, std::string username)
{
    title_ = title;
    body_ = body;
    username_ = username;
    time_stamp_ = time(NULL);
}

/**
    Mutator Function
    @param        : a reference to title of the Post
*/
void Post::setTitle(const std::string &title)
{
    title_ = title;
}

/**
    Accessor Function
    @return       : the title of the Post
*/
std::string Post::getTitle() const
{
    return title_;
}

/**
    Mutator Function
    @param        : a reference to body of the Post
*/
void Post::setBody(const std::string &body)
{
    body_ = body;
}

/**
    Accessor Function
    @return       : the body of the Post
*/
std::string Post::getBody() const
{
    return body_;
}

/**
    Mutator Function
    @param        : a reference to the username associated with this Post
*/
void Post::setUsername(const std::string &username)
{
    username_ = username;
}

/**
    Accessor Function
    @return       : username associated with this Post
*/
std::string Post::getUsername() const
{
    return username_;
}

/**
    @post         : updates the time_stamp_ to the current time
*/
void Post::updateTimeStamp()
{
    time_stamp_ = time(NULL);
}

/**
    @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
*/
void Post::getTimeStamp() const
{
    std::cout << asctime(localtime(&time_stamp_));
}
