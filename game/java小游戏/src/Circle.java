import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;

public class Circle {
	double x;
	double y;
	double a=5;
	double b=5;
	int speed = 10;
	private boolean left,up,right,down;	
	
	public void draw(Graphics g){
		if(GameFrame.live) {	
				g.setColor(Color.black);
				g.fillOval((int)x,(int)y,(int)a,(int)b);
				g.drawOval((int)x,(int)y,(int)a,(int)b);
				if(a<=20||b<=20) {
				a += 0.2;
				b += 0.2;
				}
				if(y>470){
					down = false;
				}	
				if(y<30) {
					up = false;
				}
				if(x<10){
					left = false;
				}
				if(x>470) {
					right = false;
				}	
				}
				move();
		}
		
		public void go(KeyEvent e){
			switch (e.getKeyCode()) {
			case KeyEvent.VK_LEFT:
				left = true;
				break;
			case KeyEvent.VK_UP:
				up = true;
				break;
			case KeyEvent.VK_RIGHT:
				right = true;
				break;
			case KeyEvent.VK_DOWN:
				down = true;
				break;	
			default:
				break;
			}
		}

		public void stop(KeyEvent e){
			switch (e.getKeyCode()) {
			case KeyEvent.VK_LEFT:
				left = false;
				break;
			case KeyEvent.VK_UP:
				up = false;
				break;
			case KeyEvent.VK_RIGHT:
				right = false;
				break;
			case KeyEvent.VK_DOWN:
				down = false;
				break;
			default:
				break;
			}
		}
		
		public void move(){
			if(left){
				x -= speed;
			}
			if(right){
				x += speed;
			}
			if(up){
				y -= speed;
			}
			if(down){
				y += speed;
			}
			
		}
	
		public Rectangle getRect() {
			Rectangle r = new Rectangle((int)x,(int)y,(int)a,(int)b);
			return r;
		}
	}

