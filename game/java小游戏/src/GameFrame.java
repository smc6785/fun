import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Date;


public class GameFrame extends Frame  { 
	
	private static final long serialVersionUID = 1L;
	Bullet b = new Bullet();
	Circle c = new Circle();
	
	Date startTime;
	Date endTime;	
	
	public void launchFreame() {
		setSize(500,500);
		setVisible(true);
		setResizable(false);
		startTime = new Date();
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		new PaintThread().start(); 
	}
	 
		static ArrayList<Bullet>  bulletList = new ArrayList<Bullet>();
		//调用 画笔
		public void paint(Graphics g) {
		if(live) {
			c.draw(g);	
			for(int i=0;i<bulletList.size();i++){
			Bullet b = (Bullet) bulletList.get(i);
			boolean collision = b.getRect().intersects(c.getRect());
			b.draw(g);
			if(collision) {
				GameFrame.setLive(false);
				endTime = new Date();
					}	
		}
			GameOver(g, "push arrows to dogge the reds ", 25,100,200,Color.blue);
			GameOver(g, "dogge ball ", 40,250,250,Color.black);
		}else {
			c.a=0;
			c.b=0;
			GameOver(g, "you are dead", 20,100,200,Color.blue);
			int period = (int)((endTime.getTime()-startTime.getTime())/1000);
			GameOver(g, "you survived "+ period+" s", 40,50,100,Color.cyan);
		}
	
	} 
		
		public void GameOver(Graphics g,String str,int size,int x,int y,Color color){
				Color c = g.getColor();
				g.setColor(color);
				Font f = new Font("宋体",Font.BOLD,size);
				g.setFont(f);
				g.drawString(str,x,y);
				g.setColor(c);	
			}
		
		public static void main(String[]agrs) {
			GameFrame gf = new GameFrame();
			gf.launchFreame();
			gf.move();
			for(int i=0;i<65;i++){
				Bullet b= new Bullet();
				bulletList.add(b);
			}
		}
		
		public void move() {
		addKeyListener(new KeyListener1());
		}
	
		class KeyListener1 extends KeyAdapter {
		@Override
		public void keyPressed(KeyEvent e) {
			c.go(e);
			switch(e.getKeyCode()) {
			case KeyEvent.VK_SPACE:
				live = true;
				}
			}
		
		@Override
		public void keyReleased(KeyEvent e) {
			c.stop(e);
			}
		}
	
		static boolean live = true;
		public static void setLive(boolean live) {
			GameFrame.live = live;
		}
		
		//重画窗口的线程类 使用sleep（），就不过度消耗CPU
		class PaintThread extends Thread {
			public void run(){
				while(true){
					repaint();
					try {
						Thread.sleep(40); 
					} catch (InterruptedException e) {
						e.printStackTrace();
					}   
				}
			}
			
		}
}
		
		


