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
#include "Tag.h"
#include <iostream>

using std::string;
using std::vector;
using std::invalid_argument;

Tag::Tag(string tagName) : tagName(tagName), tagPosts(vector<Post*>(0)){
  if(tagName.length() < 2){
    throw invalid_argument("Tag name too short.");
  }

  if(tagName.at(0) != '#'){ 
    throw invalid_argument("Invalid first char.");
  }

  for(unsigned int c = 1; c < tagName.length(); ++c){
    if(!islower(tagName.at(c))){
      throw invalid_argument("Invalid tag name.");
    }
  }
}

string Tag::getTagName() {
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  return this->tagPosts;
}

void Tag::addTagPost(Post* post) {
  if(post == nullptr){
    throw invalid_argument("No post.");
  }
  tagPosts.push_back(post);
}
