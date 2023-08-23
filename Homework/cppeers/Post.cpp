/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"

//self-inputted includes
#include <sstream>

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  vector<string> tags;

  std::istringstream sin(this->postText);
  string word;

  while(!sin.eof()){

    string tag = "#";

    sin >> word;

    if(word.at(0) == '#'){

      for(unsigned int c = 1; c < word.length(); ++c){

        char chr = word.at(c);

        if(chr == '!' ||
          chr == ',' ||
          chr == '.' ||
          chr == '?'
          ){
            continue;
        }
        else{
          tag += tolower(word.at(c));
        }
      }
      tags.push_back(tag);
    }
  }
  return tags;
}
