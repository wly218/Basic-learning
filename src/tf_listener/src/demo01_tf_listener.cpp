/*
    创建一个缓存对象，融合多个坐标系相对关系生成一棵坐标树
    创建一个监听器，绑定缓存对象，会将所有广播器广播的数据写入缓存
    编写一个定时器，循环实现转换
*/
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/LinearMath/Quaternion.h"

using namespace std::chrono_literals;

// 3.定义节点类；
class MinimalFrameListener : public rclcpp::Node 
{
public:
    MinimalFrameListener():Node("minimal_frame_listener")
    {
        //在构造函数中创建一个缓存对象，融合多个坐标系相对关系成一棵坐标树
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        //创建一个监听器，绑定缓存对象，会将所有的广播器广播的数据写入缓存
        transform_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_,this);
        //编写一个定时器，循环实现转换
        timer_ = this->create_wall_timer(1s, std::bind(&MinimalFrameListener::on_timer,this));
    }

private:
  void on_timer(){
    try //使用异常处理机制以防在没有订阅到话题时候直接退出
    {
      //返回新的坐标帧 父级坐标系 子级坐标系 时间点【转换最新时刻的坐标帧(最常用))】
        auto transformStamped = tf_buffer_->lookupTransform("camera","laser",tf2::TimePointZero);
      //日志输出
        RCLCPP_INFO(this->get_logger(),"----------------------转换结果----------------------");
        RCLCPP_INFO(this->get_logger(),"frame_id:%s",transformStamped.header.frame_id.c_str());
        RCLCPP_INFO(this->get_logger(),"child_frame_id:%s",transformStamped.child_frame_id.c_str());
        RCLCPP_INFO(this->get_logger(),"坐标:(%.2f,%.2f,%.2f)",
                transformStamped.transform.translation.x,
                transformStamped.transform.translation.y,
                transformStamped.transform.translation.z);

    }
    catch(const tf2::LookupException& e)
    {
      RCLCPP_INFO(this->get_logger(),"坐标变换异常：%s",e.what());
    }


  }
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::TransformListener> transform_listener_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<MinimalFrameListener>());
  rclcpp::shutdown();
  return 0;
}