//
// Created by Peter Kufahl on 8/19/15.
// Bookkeeping system example.
// Message - messages of some kind
// Folder  - directories in which messages might appear
//
// each Message can appear in multiple Folders, but there will only be one copy of the contents of any single
//  Message.
// therefore, a change of the contents of one Message will automatically be reflected when we view that Message
//  from any of its associated Folders
// this means that each Message contains a set of pointers to the Folders in which it appears, and each Folder
//  will contain a set of pointers to its Messages.
// Message will have save() and remove() operations to add/remove a Message from a specified Folder.
// to make a new Message, the ctor will have the message contents but not the Folder. save() must be called to
//  associate a Message with a Folder.
//
// the STL has version of swap() for both string and set, so Message benefits from its own version. Defining a
//  swap() for Message avoids extraneous copies of _contents and _folders. However, the Message swap()
//  has to manage the Folder pointers that point to the swapped Messages.

#ifndef SAMPLE_MESSAGE_H
#define SAMPLE_MESSAGE_H

#include <string>
#include <set>
#include <iostream>

class Folder;

class Message {
	friend class Folder;
	friend void swap (Message&, Message&);
	friend void swap (Folder&, Folder&);
public:
	explicit Message(const std::string &s = "")
	: _contents(s)
	{ }

	Message(const Message&);
	Message& operator=(const Message&);
	~Message();

	void save(Folder&);
	void remove(Folder&);

	void print_contents()
	{
		std::cout << _contents << std::endl;
	}

	void set(const std::string &s = "")
	{
		_contents = s;
	}

private:
	std::string _contents;      // message text

	std::set<Folder*> _folders; // Folder objects that have this Message

	void add_to_folders(const Message&);
	void remove_from_folders();

	void add_folder(Folder* f) { _folders.insert(f); }
	void remove_folder(Folder *f) { _folders.erase(f); }
};

class Folder {
	friend class Message;
    friend void swap (Message&, Message&);
    friend void swap (Folder&, Folder&);
public:
	Folder() = default;

	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	void add_to_message(const Folder&);
	void remove_from_message();

	void print_contents()
	{
		for (auto m : _messages)
			std::cout << m->_contents << " ";
		std::cout << std::endl;
	}

private:
	void add_message(Message* m)
	{
		_messages.insert(m);
	}

	void remove_message(Message* m)
	{
		_messages.erase(m);
	}

private:
	std::set<Message*> _messages;
};

#endif //SAMPLE_MESSAGE_H
