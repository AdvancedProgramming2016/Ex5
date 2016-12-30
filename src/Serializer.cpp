

#include "Serializer.h"
/*
template<class T>
std::string Serializer::serialize(T *object) {

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

template<class T>
void Serializer::deserialize(char *buffer, int bufferSize, T *object) {

    //Deserializing a char array.
    boost::iostreams::basic_array_source<char> device(buffer, bufferSize);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    boost::archive::binary_iarchive ia(s);

    //Passing the deserialized object
    ia >> object;
}
*/