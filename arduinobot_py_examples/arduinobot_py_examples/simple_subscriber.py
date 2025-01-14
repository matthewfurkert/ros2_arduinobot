import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SimpleSubscriber(Node):
    def __init__ (self):
        super().__init__("simple_subscriber")
        self.sub_ = self.create_subscription(String, "chatter", self.msg_callback, 10)
    
    def msg_callback(self, msg):
        self.get_logger().info(f"Recieved: {msg.data}")
    
def main():
    rclpy.init()
    node = SimpleSubscriber()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()