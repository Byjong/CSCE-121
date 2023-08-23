/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;
using std::invalid_argument;

User::User(string userName) : userName(userName), userPosts(vector<Post*>(0)) {
  if(userName.length() == 0){
    throw invalid_argument("No username.");
  }

  for(unsigned int c = 0; c < userName.length(); ++c){
    if(!islower(userName.at(c))){
      throw invalid_argument("Invalid username.");
    }
  }
}

string User::getUserName() {
  return userName;
}

vector<Post*>& User::getUserPosts() {
  return this->userPosts;
}

void User::addUserPost(Post* post) {
  if(post == nullptr){
    throw invalid_argument("No post.");
  }
  userPosts.push_back(post);
}
