//
// Created by Peter Kufahl on 8/19/15.
//



#include "Message.h"

void swap(Message& lhs, Message& rhs)
{
	using std::swap;

	// remove pointers to each Message from their original respective Folders
	for (auto f : lhs._folders)
		f->remove_message(&lhs);
	for (auto f : rhs._folders)
		f->remove_message(&rhs);

	// swap the _contents and Folder pointer sets
	swap(lhs._folders, rhs._folders);           // uses swap(set&, set&)
	swap(lhs._contents, rhs._contents);         // uses swap(string&, string&)

	// add pointers to each Message to their new respective Folders
	for (auto f : lhs._folders)
		f->add_message(&lhs);
	for (auto f : rhs._folders)
		f->add_message(&rhs);
}

Message::Message(const Message &message) :
	_contents(message._contents),
    _folders(message._folders)
{
	add_to_folders(message);
}

void Message::save(Folder &folder) {

	// this operation must update the given Folder as well as this Message.
	// that's why the parameter is a Folder&, and not a Folder or const Folder&

	_folders.insert(&folder);
	folder.add_message(this);

}

void Message::add_to_folders(const Message &message) {

	for (auto f : message._folders)
		f->add_message(this);

}

void Message::remove_from_folders() {

	for (auto f : _folders)
		f->remove_message(this);

	_folders.clear();
}

Message::~Message() {

	remove_from_folders();
}

void Message::remove(Folder &folder) {

	// this operation must update the given Folder as well as this Message.
	// that's why the parameter is a Folder&, and not a Folder or const Folder&

	_folders.erase(&folder);    // take the given folder out of the list of folders
	folder.remove_message(this);

}

Message &Message::operator=(const Message &message) {

	// handle self-assignment by removing pointers to this Message from the _folders
	//  of the lhs before inserting pointers in the _folders of the rhs
	remove_from_folders();
	_contents = message._contents;
	_folders = message._folders;
	add_to_folders(message);

	// clion initially put "return initializer" here. Why?
	return *this;
}

void swap(Folder& lhs, Folder& rhs)
{
	using std::swap;

	for (auto m : lhs._messages)
		m->remove_folder(&lhs);

	for (auto m : rhs._messages)
		m->remove_folder(&rhs);

	swap (lhs._messages, rhs._messages);

	for (auto m : lhs._messages)
		m->add_folder(&lhs);

	for (auto m : rhs._messages)
		m->add_folder(&rhs);

}

void Folder::add_to_message(const Folder &folder) {

	for (auto m : folder._messages)
		m->add_folder(this);
}

Folder::Folder(const Folder &folder)
	: _messages(folder._messages)
{
	add_to_message(folder);
}


void Folder::remove_from_message() {

	for (auto m : _messages)
		m->remove_folder(this);

	_messages.clear();
}

Folder::~Folder() {

	remove_from_message();

}

Folder &Folder::operator=(const Folder &folder) {

	remove_from_message();
	_messages = folder._messages;
	add_to_message(folder);

	return *this;
}

void Message::move_folders(Message *m) {

	// worker bee for move operations
	// 1. moves the _folders set
	//      std::move() means it calls the move assignment, noit the copy assignment
	// 2. iterates through _folders, removing the ptr to the original Message
	//      and adding a ptr to the new Message
	// *  since inserting an element into a set might throw an exception, we cannot
	//     qualify this method with noexcept
	// 3. after the move, we know m._folders is invalid, but we don't know what its
	//     contents are. Therefore, we call clear() on m._folders to make it safe to
	//     destroy

	_folders = std::move(m->_folders);      // this uses the set move assignment

	// for each Folder in _folders
	for (auto f : _folders)
	{
		f->remove_message(m);               // remove the old Message from the Folder
		f->add_message(this);               // add this Message to that Folder
	}

	// make sure that destroying m is harmless
	m->_folders.clear();
}

Message::Message(Message &&m)
	: _contents(std::move(m._contents))
{
	// move ctor for Message

	// move _folders and update the Folder pointers
	move_folders(&m);
}

Message &Message::operator=(Message &&rhs) {

	// move assignment operator for Message

	// direct check for self-assignment
	if(this != &rhs)
	{
		remove_from_folders();
		_contents = std::move(rhs._contents);
		move_folders(&rhs);
	}

	return *this;
}

Folder &Folder::operator=(Folder &&rhs) {

	remove_from_message();
	_messages = std::move(rhs._messages);

	return *this;
}
