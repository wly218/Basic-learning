#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/process.hpp"

using base_interfaces_demo::action::Process;
//也是为了简化写法，注意和服务端并不是完全一致
using GoalHandleProgress = rclcpp_action::ClientGoalHandle<Process>;
using namespace std::placeholders;

class MyActionClient:public rclcpp::Node
{
public:
    explicit MyActionClient(const rclcpp::NodeOptions& node_options =rclcpp::NodeOptions()):Node("action_client",node_options)
    {
        //建立动作客户端
        this->client_ = rclcpp_action::create_client<Process>(this,"get_sum");
    }
    void send_goal(int64_t num)
    {
        //如果指针不存在，那么说明动作客户端没有初始化
        if(!this->client_)
        {
            //提示错误信息
            RCLCPP_ERROR(this->get_logger(),"动作客户端尚未初始化");
            return;
        }
        //在参数中不断尝试连接
        if(!this->client_->wait_for_action_server(std::chrono::seconds(10)))
        {
            RCLCPP_ERROR(this->get_logger(),"服务连接失败！");
            return;
        }
        auto goal_msg = Process::Goal();
        goal_msg.num = num;
        RCLCPP_INFO(this->get_logger(),"发送请求数据！");
        auto send_goal_options = rclcpp_action::Client<Process>::SendGoalOptions();
        send_goal_options.goal_response_callback = std::bind(&MyActionClient::goal_response_callback,this,_1);
        send_goal_options.feedback_callback = std::bind(&MyActionClient::feedback_callback,this,_1,_2);
        send_goal_options.result_callback = std::bind(&MyActionClient::result_callback,this,_1);
        auto goal_handle_future = this->client_->async_send_goal(goal_msg,send_goal_options);
    }
private:
    rclcpp_action::Client<Process>::SharedPtr client_;
    //处理目标发送后的反馈
    void goal_response_callback(GoalHandleProgress::SharedPtr goal_handle)
    {
        if(!goal_handle)
        {
            RCLCPP_ERROR(this->get_logger(),"目标请求服务器被拒绝！");
        }else{
            RCLCPP_INFO(this->get_logger(),"目标被接受，等待结果中");
        }
    }
    //处理连续反馈
    void feedback_callback(GoalHandleProgress::SharedPtr,const std::shared_ptr<const Process::Feedback> feedback)
    {
        int32_t progress = (int32_t)(feedback->process*100);
        RCLCPP_INFO(this->get_logger(),"当前进度：%d%%",progress);
    }
    //处理最终响应
    void result_callback(const GoalHandleProgress::WrappedResult& result)
    {
        //根据最终响应返回的状态来...
        switch (result.code)
        {
        case rclcpp_action::ResultCode::SUCCEEDED:
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(),"任务被中止");
            return;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_WARN(this->get_logger(),"任务被取消");
            return;
        default:
            RCLCPP_ERROR(this->get_logger(),"未知异常");
            return;
        }
        RCLCPP_INFO(this->get_logger(),"任务执行完毕，最终结果为：%ld",result.result->sum);
    }
};

int main(int argc,char** argv)
{
    //初始化客户端
    rclcpp::init(argc,argv);
    //创建动作客户端指针
    auto action_client = std::make_shared<MyActionClient>();
    //利用成员函数将目标数据发送给服务端
    action_client->send_goal(20);
    //传入指针并且挂起
    rclcpp::spin(action_client);
    rclcpp::shutdown();
    return 0;
}