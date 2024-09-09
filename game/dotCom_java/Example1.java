import java.awt.*;
import javax.swing.*;
public class Example1 extends JFrame{
	public void CreateJFrame(String title){
		JFrame jf = new JFrame(title);
		Container container = jf.getContentPane();
		JLabel jl = new JLabel("杜伟志是个痞子");
		jl.setHorizontalAlignment(SwingConstants.CENTER);
		container.add(jl);
		container.setBackground(Color.red);
		jf.setVisible(false);
		jf.setSize(200,150);

		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	public static void main(String[] args) {
		new Example1().CreateJFrame("123");
	}
}