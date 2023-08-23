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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::cout;
using std::ifstream;
using std::invalid_argument;
using std::istringstream;
using std::runtime_error;
using std::string;
using std::vector;

Network::Network() : users(vector<User *>()), posts(vector<Post *>()), tags(vector<Tag *>())
{
  return;
}

void Network::loadFromFile(string fileName)
{
  ifstream fin(fileName);
  if (!fin.is_open())
  {
    throw invalid_argument("Couldn't open file.");
  }

  while (!fin.eof())
  {
    string line = "";
    getline(fin, line);
    istringstream sin(line);

    if (line.empty())
    {
      break;
    }

    string word = "";
    sin >> word;

    if (word == "User")
    {
      string userName = "";
      sin >> userName;
      if (userName.empty())
        throw runtime_error("No username provided.");

      try
      {
        this->addUser(userName);
      }
      catch (const std::exception &err)
      {
        throw runtime_error(err.what());
      }
    }

    else if (word == "Post")
    {
      unsigned int postId = 0;
      sin >> postId;
      if (sin.fail())
      {
        throw runtime_error("Invalid ID.");
      }

      string userName = "";
      sin >> userName;
      if (userName.empty())
        throw runtime_error("No username provided.");

      string post_text = "";
      while (!sin.eof())
      {
        sin >> word;
        post_text += word + (sin.peek() == EOF ? "" : " ");
      }

      if (post_text.empty())
        throw runtime_error("Post text is empty.");

      try
      {
        this->addPost(postId, userName, post_text);
      }
      catch (const std::exception &err)
      {
        throw std::runtime_error(err.what());
      }
    }

    else
    {
      throw runtime_error("Invalid information input.");
    }
  }
}

void Network::addUser(string userName)
{
  for (unsigned int c = 0; c < userName.size(); ++c)
  {
    userName.at(c) = tolower(userName.at(c));
  }

  for (unsigned int i = 0; i < users.size(); ++i)
  {
    if (userName == users.at(i)->getUserName())
    {
      throw invalid_argument("User already exists.");
    }
  }
  users.push_back(new User(userName));
  cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText)
{
  for (Post *post : this->posts)
  {
    if (post->getPostId() == postId)
      throw invalid_argument("Post ID already exists.");
  }

  bool exist = false;
  User *u = nullptr;
  for (User *user : this->users)
  {
    if (user->getUserName() == userName)
    {
      exist = true;
      u = user;
      break;
    }
  }

  if (!exist)
    throw invalid_argument("User doesn't exist.");

  Post *post = new Post(postId, userName, postText);

  for (string tag : post->findTags())
  {
    exist = false;
    for (Tag *t : this->tags)
    {
      if (t->getTagName() == tag)
      {
        t->addTagPost(post);
        exist = true;
        break;
      }
    }

    if (!exist)
    {
      try
      {
        Tag *new_tag = new Tag(tag);
        new_tag->addTagPost(post);
        this->tags.push_back(new_tag);
      }
      catch (const std::exception &err)
      {
        continue;
      }
    }
  }

  this->posts.push_back(post);
  u->addUserPost(post);
  cout << "Added Post " << std::to_string(postId) << " by " << userName << "\n";
}

vector<Post *> Network::getPostsByUser(string userName)
{
  if (userName.empty())
  {
    throw invalid_argument("User doesn't exist.");
  }

  bool exist = false;
  User *user;
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    if (users.at(i)->getUserName() == userName)
    {
      user = users.at(i);
      exist = true;
      break;
    }
  }
  if (!exist)
  {
    throw invalid_argument("User doesn't exist");
  }

  vector<Post *> temp;

  for (Post *post : user->getUserPosts())
  {
    temp.push_back(post);
  }
  return temp;
}

vector<Post *> Network::getPostsWithTag(string tagName)
{
  if (tagName.empty())
  {
    throw invalid_argument("Tag doesn't exist");
  }

  bool exist = false;
  for (Tag *tag : this->tags)
  {
    if (tag->getTagName() == tagName)
    {
      exist = true;
    }
  }

  if (!exist)
  {
    throw invalid_argument("Tag doesn't exist");
  }

  vector<Post *> temp;

  for (Post *post : posts)
  {
    for (string tag : post->findTags())
    {
      if (tag == tagName)
      {
        temp.push_back(post);
      }
    }
  }
  return temp;
}

vector<string> Network::getMostPopularHashtag()
{
  vector<string> temp;
  unsigned int max = 0;
  for (Tag *tag : this->tags)
  {
    size_t sz = tag->getTagPosts().size();
    if (sz > max)
    {
      max = sz;
    }
  }

  for (Tag *tag : this->tags)
  {
    if (tag->getTagPosts().size() == max)
    {
      temp.push_back(tag->getTagName());
    }
  }

  return temp;
}

/**
 * Destructor
 * Do not change; already implemented.
 */
Network::~Network()
{
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i)
  {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i)
  {
    delete posts.at(i);
  }
}
