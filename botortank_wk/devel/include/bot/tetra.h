// Generated by gencpp from file bot/tetra.msg
// DO NOT EDIT!


#ifndef BOT_MESSAGE_TETRA_H
#define BOT_MESSAGE_TETRA_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace bot
{
template <class ContainerAllocator>
struct tetra_
{
  typedef tetra_<ContainerAllocator> Type;

  tetra_()
    : a(false)
    , b(false)
    , c(false)
    , d(false)  {
    }
  tetra_(const ContainerAllocator& _alloc)
    : a(false)
    , b(false)
    , c(false)
    , d(false)  {
  (void)_alloc;
    }



   typedef uint8_t _a_type;
  _a_type a;

   typedef uint8_t _b_type;
  _b_type b;

   typedef uint8_t _c_type;
  _c_type c;

   typedef uint8_t _d_type;
  _d_type d;




  typedef boost::shared_ptr< ::bot::tetra_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bot::tetra_<ContainerAllocator> const> ConstPtr;

}; // struct tetra_

typedef ::bot::tetra_<std::allocator<void> > tetra;

typedef boost::shared_ptr< ::bot::tetra > tetraPtr;
typedef boost::shared_ptr< ::bot::tetra const> tetraConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bot::tetra_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bot::tetra_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace bot

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'bot': ['/home/botortank/botortank_ws/src/bot/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::bot::tetra_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bot::tetra_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bot::tetra_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bot::tetra_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bot::tetra_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bot::tetra_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bot::tetra_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a10316242c9f6651bd3958b5cd4982fa";
  }

  static const char* value(const ::bot::tetra_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa10316242c9f6651ULL;
  static const uint64_t static_value2 = 0xbd3958b5cd4982faULL;
};

template<class ContainerAllocator>
struct DataType< ::bot::tetra_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bot/tetra";
  }

  static const char* value(const ::bot::tetra_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bot::tetra_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool a\n\
bool b\n\
bool c\n\
bool d\n\
";
  }

  static const char* value(const ::bot::tetra_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bot::tetra_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.a);
      stream.next(m.b);
      stream.next(m.c);
      stream.next(m.d);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct tetra_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bot::tetra_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bot::tetra_<ContainerAllocator>& v)
  {
    s << indent << "a: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.a);
    s << indent << "b: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.b);
    s << indent << "c: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.c);
    s << indent << "d: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.d);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BOT_MESSAGE_TETRA_H
