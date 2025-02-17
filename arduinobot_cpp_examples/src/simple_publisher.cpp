#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SimplePublisher : public rclcpp::Node
{
public:
  SimplePublisher() : Node("simple_publisher"), counter_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&SimplePublisher::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "SimplePublisher has been started (1 Hz).");
  }
private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, ROS2 - counter: " + std::to_string(counter_++);
        publisher_->publish(message);
    }

    unsigned int counter_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimplePublisher>());
  rclcpp::shutdown();
  return 0;
}