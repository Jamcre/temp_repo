/*
Author: James Michael Crespo
File Name: main.cpp
Date of Creation: 10/12/2022

Description: This file contains the tests for Project 4.
*/
#include "Network.hpp"
#include "LinkedList.hpp"
#include "Account.hpp"
#include "General.hpp"
#include "Post.hpp"
#include "Poll.hpp"
#include "Promotional.hpp"
#include <iostream>
#include <vector>

int main()
{
    // // TASK 1 TESTS
    // std::cout << "\nTASK 1 TESTS: " << std::endl;

    // // CREATING NETWORK
    // Network<Account> net1;

    // // CREATING ACCOUNTS
    // Account *acc1 = new Account("user1", "pass1");
    // Account *acc2 = new Account("user2", "pass2");
    // Account *acc3 = new Account("user3", "pass3");

    // // ADDING ACCOUNTS TO NETWORK
    // net1.addAccount(acc1);
    // net1.addAccount(acc2);
    // net1.addAccount(acc3);

    // // TESTING GENERAL CLASS CREATION WITH POLYMORPHISM
    // Post *ptr_general1 = new General("General class polymorphism test!", "This post will test polymorphism between Post class and General class. user1", "user1");
    // Post *ptr_general2 = new General("2nd General class polymorphism test!", "This is the 2nd post will test polymorphism between Post class and General class.(user1)", "user1");
    // Post *ptr_general3 = new General("3rd General class polymorphism test!", "This is the 3rd post will test polymorphism between Post class and General class.(user 3)", "user3");

    // // TESTING POLL CLASS CREATION WITH POLYMORPHISM
    // std::vector<std::string> poll_options;
    // poll_options.push_back("Male");
    // poll_options.push_back("Female");
    // Post *ptr_poll1 = new Poll("Poll class polymorphism test!", "What gender are you?(user1)", "user1", poll_options);

    // // TESTING PROMOTIONAL CLASS CREATION WITH POLYMORPHISM
    // Post *ptr_promotional1 = new Promotional("Promotional class polymorphism test!", "This post will test polymorphism between Post class and Promotional class.(user1)", "user1", "https://www.testlink.com");
    // Post *ptr_promotional2 = new Promotional("2nd Promotional class object!", "This is the 2nd Promotional class object created and will be made by (user2)", "user2", "https://www.notvirus.real");

    // // 'Account' addPost Test
    // std::cout << "\n'Account' addPost Test: " << std::endl;
    // if (acc1->addPost(ptr_promotional1) == acc1->addPost(ptr_general1) == acc1->addPost(ptr_poll1) == acc1->addPost(ptr_general2))
    // {
    //     std::cout << "General, Poll, and Promotional objects sucessfully added to Account" << std::endl;
    //     std::cout << "TEST PASSED" << std::endl;
    // }

    // // 'Account' viewPosts Test
    // std::cout << "\n'Account' viewPost Test: " << std::endl;
    // acc1->viewPosts();
    // std::cout << "\nTEST PASSED" << std::endl;

    // // 'Network' addToFeed Test
    // std::cout << "\n'Network' addToFeed Test: " << std::endl;
    // if (net1.addToFeed(ptr_promotional2))
    // {
    //     std::cout << "Promotional object added to network feed" << std::endl;
    //     std::cout << "TEST PASSED" << std::endl;
    // }

    // // 'Network' printFeedForAccount Test
    // acc2->followAccount("user1");
    // acc2->followAccount("user3");
    // acc3->addPost(ptr_general3);
    // std::cout << "\n'Network' printFeedForAccount Test: " << std::endl;
    // net1.printFeedForAccount(*acc2);
    // std::cout << "\nTEST PASSED" << std::endl;

    // TASK 2 TESTS
    // std::cout << "\nTASK 2 TESTS: " << std::endl;

    // // 'LinkedList' copy constructor Test
    // LinkedList<Post *> posts;
    // std::vector<std::string> poll2_options;
    // poll2_options.push_back("Yes");
    // poll2_options.push_back("No");
    // Post *ptr_general4 = new General("General post number 4", "Body of general post 4(user 4)", "user4");
    // Post *ptr_poll2 = new Poll("Poll post number 2", "Body of poll post 2(user 4)", "user4", poll2_options);
    // Post *ptr_general5 = new General("General post number 5", "Body of general post 5(user 5)", "user5");
    // Post *ptr_promotional3 = new Promotional("Promotional post number 3", "Body of promotional post 5(user 5)", "user5", "https://www.google.com");
    // std::cout << "\n'LinkedList' copy constructor Test: " << std::endl;
    // posts.insert(ptr_general4, 0);
    // posts.insert(ptr_poll2, 0);
    // posts.insert(ptr_general5, 0);
    // posts.insert(ptr_promotional3, 0);

    // LinkedList<Post *> posts_copy = posts;
    // Node<Post *> *temp = posts_copy.getHeadPtr();
    // while (temp != nullptr)
    // {
    //     temp->getItem()->displayPost();
    //     temp = temp->getNext();
    // }

    // std::cout << "\nTEST PASSED" << std::endl;

    // // 'LinkedList' reverseCopy Test
    // std::cout << "\n'LinkedList' reverseCopy Test: " << std::endl;
    // posts_copy.reverseCopy(posts);
    // Node<Post *> *temp2 = posts_copy.getHeadPtr();
    // while (temp2 != nullptr)
    // {
    //     temp2->getItem()->displayPost();
    //     temp2 = temp2->getNext();
    // }
    // std::cout << "\nTEST PASSED" << std::endl;

    // // 'LinkedList' moveItemToTop Test
    // std::cout << "\n'LinkedList' moveItemToTop Test: " << std::endl;
    // if (posts_copy.moveItemToTop(ptr_promotional3))
    // {
    //     Node<Post *> *temp3 = posts_copy.getHeadPtr();
    //     while (temp3 != nullptr)
    //     {
    //         temp3->getItem()->displayPost();
    //         temp3 = temp3->getNext();
    //     }
    // }
    // std::cout << "\nTEST PASSED" << std::endl;

    // 'Network' removeIfContains Test
    std::cout << "\n'Network' removeIfContains Test: " << std::endl;

    Network<Account> net2;                            // create net2
    Account *acc10 = new Account("user10", "pass10"); // create accounts
    Account *acc11 = new Account("user11", "pass11");
    Account *acc12 = new Account("user12", "pass12");
    net2.addAccount(acc10); // add accounts
    net2.addAccount(acc11);
    net2.addAccount(acc12);
    Post *ptr_general6 = new General("General post number 6", "Body of general post 6 (user 12)", "user12"); // create posts
    Post *ptr_general7 = new General("General post number 7", "Body of general post 7 (user 11)", "user11");
    Post *ptr_general8 = new General("General post number 8", "Body of general post 8 (user 10)", "user10");
    Post *ptr_promotional4 = new Promotional("Promotional post number 4", "Body of promotional post 4 (user 12)", "user12", "https://www.google.com");
    Post *ptr_promotional5 = new Promotional("Promotional post number 5", "Body of promotional post 5 (user 11)", "user11", "https://www.yahoo.com");
    acc10->addPost(ptr_general8); // add posts to accounts
    acc11->addPost(ptr_general7);
    acc11->addPost(ptr_promotional4);
    acc12->addPost(ptr_general6);
    acc12->addPost(ptr_promotional5);
    int removed = net2.removeIfContains("(user 11)");
    std::cout << "\nNumber of posts removed: " << removed << std::endl;

    if (removed == 2)
    {
        Node<Post *> *temp4 = net2.getNetworkFeed().getHeadPtr();
        while (temp4 != nullptr)
        {
            temp4->getItem()->displayPost();
            temp4 = temp4->getNext();
        }
        std::cout << "\nNumber of posts removed: " << removed << std::endl;
        std::cout << "\nTEST PASSED" << std::endl;
    }
}
