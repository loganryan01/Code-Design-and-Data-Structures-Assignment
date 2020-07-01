/*------------------------------------------------------------
	File Name: HashTable.h
	Purpose: Hold all the functions to control the hash table.
	Author: Logan Ryan
	Modified: 29/06/2020
--------------------------------------------------------------
	Copyright Logan Ryan 2020.
------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <vector> 

// This bucket is taken
#define TAKEN 1;

template<class KeyType, class T>
class HashTable
{
public:
	// Constructor
	HashTable(unsigned int size) 
		: m_size(size) {};
	// Destructor
	~HashTable() {};

	// Operators to allow the m_data to be checked like an array.
	T& operator [] (const KeyType& key)
	{
		auto hashedKey = BKDRHash(key) % m_size;
		return m_data[hashedKey];
	}

	const T& operator [] (const KeyType& key) const
	{
		auto hashedKey = BKDRHash(key) % m_size;
		return m_data[hashedKey];
	}

	// Check if the key exists in the hash table
	bool HasValue(const KeyType& key)
	{	
		// if the vector is empty, return false
		if (m_key.empty())
		{
			return false;
		}
		
		// move in array until whole array is checked
		for (unsigned int hashIndex = BKDRHash(key) % m_size; hashIndex < m_size; hashIndex++)
		{	
			// if the key matches any of the keys in the key array
			if (m_key[hashIndex] == key)
			{
				// return true
				return true;
			}

			// other wise continue the search
		}
		
		// the key does not exist in the hash table
		return false;
	}

	// Get the texture from the hash table
	T& GetValue(const KeyType& key)
	{
		// The index for the hash table
		unsigned int hashIndex = 0;

		// No texture
		T nullTexture = { 0,0,0,0,0 };

		// At this stage the texture does not exists
		T& texture = nullTexture;

		// Check the key vector, if the key matches any of the keyes, return the data from the index
		for (hashIndex = BKDRHash(key) % m_size; hashIndex < m_size; hashIndex++)
		{
			if (m_key[hashIndex] == key)
			{
				// If the key matches any of the keyes, Then the texture that has been found
				texture = m_data[hashIndex];
				
				break;
			}
		}

		// If the texture does not exist return a null texture
		return texture;
	}

	// Set the texture to the correct position in the hash table
	void SetValue(const KeyType& key, const T& value)
	{
		// Create a hash for the key
		unsigned int hashIndex = 0;

		// Resize the arrays
		if (m_key.size() < m_size)
		{
			m_key.resize(m_size);
		}

		if (m_data.size() < m_size)
		{
			m_data.resize(m_size);
		}

		if (m_space.size() < m_size)
		{
			m_space.resize(m_size);
		}

		// Go through the hash table to find a free spot and place the data and its key
		for (hashIndex = BKDRHash(key) % m_size; hashIndex < m_size; hashIndex++)
		{
			// Check if the bucket is empty
			if (m_space[hashIndex] == 0)
			{
				// Set the key
				m_key[hashIndex] = key;

				// Set the value
				m_data[hashIndex] = value;

				// Make that space full
				m_space[hashIndex] = TAKEN;
				break;
			}
		}
	}

private:
	// Hash Function
	unsigned int BKDRHash(const KeyType& key)
	{
		// hash value
		unsigned int hash = 0;

		// convert keytype to string
		std::string temp = key;

		// convert key to hash
		for (unsigned int i = 0; i < temp.length(); i++)
		{
			hash = (hash * 1313) + temp[i];
		}

		// return the hash
		return (hash & 0x7FFFFFFF);
	}

	// array to store textures
	std::vector<T> m_data;

	// vector to store the keyes
	std::vector<KeyType> m_key;

	// Array to check if there is an empty spot in the hash table
	std::vector<int> m_space;

	// size of the arrays
	unsigned int m_size;
};

