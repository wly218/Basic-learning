#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/process.hpp"

using namespace std::placeholders;
using base_interfaces_demo::action::Process;
//也是为了简化写法
using GoalHandleProgress = rclcpp_action::ServerGoalHandle<Process>;

class MyActionServer:public rclcpp::Node
{
public:
    //这里的构造函数不太一样，需要注意
    explicit MyActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions()):Node("action_server",options)
    {
        this->action_server_ = rclcpp_action::create_server<Process>(
          this,
          "get_sum",
          std::bind(&MyActionServer::handle_goal,this,_1,_2),
          std::bind(&MyActionServer::handle_cancel,this,_1),
          std::bind(&MyActionServer::handle_accepted,this,_1));
          RCLCPP_INFO(this->get_logger(),"服务端创建成功，正在接受数据..");
    } 
private:
     //这是动作客户端的指针
     rclcpp_action::Server<Process>::SharedPtr action_server_;
     //处理请求数据
     rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID& uuid,std::shared_ptr<const Process::Goal> goal)
     {
        //貌似 uuid 是分配的一个序列号还是什么玩意
        (void)uuid;
        //提示收到请求的数据
        RCLCPP_INFO(this->get_logger(),"接收到客户端口请求，请求数字为：%ld",goal->num);
        //收到数据要判断其合理性
        if(goal->num<1)
        {
          //不符合则拒绝接受数据
          return rclcpp_action::GoalResponse::REJECT;
        }
        //接收数据并且立刻执行
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
     }   
     //处理取消任务请求
     rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleProgress> goal_handle)
     {
        //虽然但是为什么没有用到 goal_handle
        (void)goal_handle;
        RCLCPP_INFO(this->get_logger(),"接收到任务取消请求！");
        return rclcpp_action::CancelResponse::ACCEPT;
     }
     //执行任务的函数
     void execute(const std::shared_ptr<GoalHandleProgress> goal_handle)
     {
        RCLCPP_INFO(this->get_logger(),"开始执行任务");
        //设置一个休眠周期
        rclcpp::Rate loop_rate(10.0);
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<Process::Feedback>();
        auto result = std::make_shared<Process::Result>();
        int64_t sum = 0;
        for(int i = 1;(i <= goal->num) && rclcpp::ok();i++)
        {
            sum+=1;
            if(goal_handle->is_canceling())
            {
              result->sum = sum;
              goal_handle->canceled(result);
              RCLCPP_INFO(this->get_logger(),"任务取消");
              return;
            }
            feedback->process = (double_t)i/goal->num;
            goal_handle->publish_feedback(feedback);
            RCLCPP_INFO(this->get_logger(),"连续反馈中，进度：%.2f",feedback->process);
            loop_rate.sleep();
        }
        if(rclcpp::ok())
        {
          result->sum = sum;
          goal_handle->succeed(result);
          RCLCPP_INFO(this->get_logger(),"任务完成！");
        }
     }
     //生成连续反馈
     void handle_accepted(const std::shared_ptr<GoalHandleProgress> goal_handle)
     {
        //建立连续反馈的线程
        std::thread{std::bind(&MyActionServer::execute,this,_1),goal_handle}.detach();
     }
};

int main(int argc,char** argv)
{
  //初始化ROS2客户端
  rclcpp::init(argc,argv);
  //创建节点指针
  auto action_server = std::make_shared<MyActionServer>();
  //传入节点指针
  rclcpp::spin(action_server);
  //释放资源
  rclcpp::shutdown();
  return 0;
}