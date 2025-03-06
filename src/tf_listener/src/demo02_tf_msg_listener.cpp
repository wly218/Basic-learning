#include <geometry_msgs/msg/point_stamped.hpp>
#include <message_filters/subscriber.h> //特殊的订阅方

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/create_timer_ros.h> //定时器【该定时器平时基本不用】
#include <tf2_ros/message_filter.h> //过滤器
#include <tf2_ros/transform_listener.h>
// #ifdef TF2_CPP_HEADERS
//   #include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
// #else
//   #include <tf2_geometry_msgs/tf2_geometry_msgs.h>
// #endif

#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

using namespace std::chrono_literals;

// 3.定义节点类；
class MessageFilterPointListener : public rclcpp::Node
{
public:
  MessageFilterPointListener(): Node("message_filter_point_listener")
  {

    target_frame_ = "base_link";

    typedef std::chrono::duration<int> seconds_type;
    seconds_type buffer_timeout(1);
    // 创建tf缓存对象指针
    tf2_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    // 很莫名其妙的一个东西
    auto timer_interface = std::make_shared<tf2_ros::CreateTimerROS>(
      this->get_node_base_interface(),
      this->get_node_timers_interface());
    // 创建一个定时器接口
    tf2_buffer_->setCreateTimerInterface(timer_interface);
    // 创建tf监听器绑定缓存对象
    tf2_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf2_buffer_); 

    // 创建坐标点订阅方并订阅指定话题【实例化的时候使用的是无参构造，这里使用内置的函数订阅指定话题】
    point_sub_.subscribe(this, "point");
    // 创建消息过滤器过滤被处理的数据
    //订阅对象 缓存 目标坐标系 队列长度 日志接口 时钟接口 超时时间
    tf2_filter_ = std::make_shared<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>>(
      point_sub_, 
      *tf2_buffer_, 
      target_frame_, 
      10, 
      this->get_node_logging_interface(),
      this->get_node_clock_interface(), 
      buffer_timeout);
    // 为消息过滤器注册转换坐标点数据的回调函数
    tf2_filter_->registerCallback(&MessageFilterPointListener::msgCallback, this);
  }

private:
  void msgCallback(const geometry_msgs::msg::PointStamped::SharedPtr point_ptr)
  {
    geometry_msgs::msg::PointStamped point_out;
    try {
      tf2_buffer_->transform(*point_ptr, point_out, target_frame_);
      RCLCPP_INFO(
        this->get_logger(), "坐标点相对于base_link的坐标:(%.2f,%.2f,%.2f)",
        point_out.point.x,
        point_out.point.y,
        point_out.point.z);
    } catch (tf2::TransformException & ex) {
      RCLCPP_WARN(
        // Print exception which was caught
        this->get_logger(), "Failure %s\n", ex.what());
    }
  }
  std::string target_frame_;
  std::shared_ptr<tf2_ros::Buffer> tf2_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf2_listener_;
  message_filters::Subscriber<geometry_msgs::msg::PointStamped> point_sub_;
  std::shared_ptr<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>> tf2_filter_;
};

int main(int argc, char ** argv)
{
  // 2.初始化 ROS 客户端；
  rclcpp::init(argc, argv);
  // 4.调用 spin 函数，并传入对象指针；
  rclcpp::spin(std::make_shared<MessageFilterPointListener>());
  // 5.释放资源。
  rclcpp::shutdown();
  return 0;
}