#include "rclcpp/rclcpp.hpp" //允许使用ROS2系统中常见的组件
#include "base_interfaces_demo/msg/student.hpp" //包含了用于发布数据的内置数据类型
//使用时间单位
using namespace std::chrono_literals;
//简化写法
using base_interfaces_demo::msg::Student;
//继承ROS2的基础节点创建自己的节点类
class MyPub:public rclcpp::Node
{
public:
    //在构造函数中向基类节点传入节点名参数，并初始化成员变量count_为0
    MyPub():Node("topic_publisher"),count_(0)
    {
        //创建发布方，Student为发布信息类型,"my_topic"是话题名，10是信息队列长度
        publisher_ = this->create_publisher<Student>("my_topic",10);
        //创建定时器，使timer_callback每秒执行一次
        timer_ = this->create_wall_timer(1s,std::bind(&MyPub::timer_callback,this));
        //std::bind是一个函数模板，用于创建函数对象
        //这里绑定了成员函数，将对象的成员函数和对象本身绑定到一起，从而创建一个函数对象
        //这在需要将成员函数作为回调函数传递时候非常有用
    }
private:
    //这个函数是设置消息数据并实际发布数据的函数
    void timer_callback()
    {
        auto stu = Student(); //auto在C++里可以自动识别数据类型，避免冗杂的数据类型影响可读性
        //初始化类的成员变量
        stu.name = "骨架";
        stu.age = count_++;
        stu.height = 1.80;
        //切记组织好信息后要发布出去！！！
        publisher_->publish(stu);
        RCLCPP_INFO(this->get_logger(),"学生信息为：姓名：%s,年龄：%d,身高：%.2f",stu.name.c_str(),stu.age,stu.height);
    }
    //成员变量有定时器，发布方指针，还有一个没什么用的计数器，表示年龄的增长
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<Student>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc,char** argv)
{
    //初始化ROS2客户端
    rclcpp::init(argc,argv);
    //调用spin函数，并传入节点对象指针
    //可以直接在参数中创建，也可以创建后将变量传入
    //处理来自节点的数据，包括定时器的回调函数
    rclcpp::spin(std::make_shared<MyPub>());
    //释放资源
    rclcpp::shutdown();
    return 0;
}