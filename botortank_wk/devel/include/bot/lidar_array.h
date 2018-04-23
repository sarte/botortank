// Generated by gencpp from file bot/lidar_array.msg
// DO NOT EDIT!


#ifndef BOT_MESSAGE_LIDAR_ARRAY_H
#define BOT_MESSAGE_LIDAR_ARRAY_H


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
struct lidar_array_
{
  typedef lidar_array_<ContainerAllocator> Type;

  lidar_array_()
    : angles()
    , distances()
    , iter(0)  {
      angles.assign(0.0);

      distances.assign(0.0);
  }
  lidar_array_(const ContainerAllocator& _alloc)
    : angles()
    , distances()
    , iter(0)  {
  (void)_alloc;
      angles.assign(0.0);

      distances.assign(0.0);
  }



   typedef boost::array<float, 360>  _angles_type;
  _angles_type angles;

   typedef boost::array<float, 360>  _distances_type;
  _distances_type distances;

   typedef uint8_t _iter_type;
  _iter_type iter;





  typedef boost::shared_ptr< ::bot::lidar_array_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bot::lidar_array_<ContainerAllocator> const> ConstPtr;

}; // struct lidar_array_

typedef ::bot::lidar_array_<std::allocator<void> > lidar_array;

typedef boost::shared_ptr< ::bot::lidar_array > lidar_arrayPtr;
typedef boost::shared_ptr< ::bot::lidar_array const> lidar_arrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bot::lidar_array_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bot::lidar_array_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::bot::lidar_array_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bot::lidar_array_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bot::lidar_array_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bot::lidar_array_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bot::lidar_array_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bot::lidar_array_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bot::lidar_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a3ddce690af809517c1ac0a3e62abcfa";
  }

  static const char* value(const ::bot::lidar_array_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa3ddce690af80951ULL;
  static const uint64_t static_value2 = 0x7c1ac0a3e62abcfaULL;
};

template<class ContainerAllocator>
struct DataType< ::bot::lidar_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bot/lidar_array";
  }

  static const char* value(const ::bot::lidar_array_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bot::lidar_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32[360] angles\n\
float32[360] distances\n\
uint8  iter\n\
";
  }

  static const char* value(const ::bot::lidar_array_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bot::lidar_array_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.angles);
      stream.next(m.distances);
      stream.next(m.iter);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct lidar_array_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bot::lidar_array_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bot::lidar_array_<ContainerAllocator>& v)
  {
    s << indent << "angles[]" << std::endl;
    for (size_t i = 0; i < v.angles.size(); ++i)
    {
      s << indent << "  angles[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.angles[i]);
    }
    s << indent << "distances[]" << std::endl;
    for (size_t i = 0; i < v.distances.size(); ++i)
    {
      s << indent << "  distances[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.distances[i]);
    }
    s << indent << "iter: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.iter);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BOT_MESSAGE_LIDAR_ARRAY_H
