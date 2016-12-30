#include <iostream>
#include "../sockets/Udp.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#ifndef EX4_SERIALIZER_H
#define EX4_SERIALIZER_H


class Serializer {

public:

    /**
     * The method serialized a given object into a string.
     * @param object
     * @return string holding the serialized object
     */
    template <class T>
    std::string serialize(T *object){
        //The string holds the final serialized object
        std::string serialString;

        //Serializing to string
        boost::iostreams::back_insert_device<std::string> inserter(serialString);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << object;
        s.flush();

        return serialString;
    }

    /**
     * The method deserializes the given char buffer into the given object.
     * @param buffer
     * @param bufferSize
     * @param object
     */
    template <class T>
    void deserialize(char *buffer, int bufferSize, T *&object){
        //Deserializing a char array.
        boost::iostreams::basic_array_source<char> device(buffer, bufferSize);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
        boost::archive::binary_iarchive ia(s);

        //Passing the deserialized object
        ia >> object;
    }
};


#endif //EX4_SERIALIZER_H
