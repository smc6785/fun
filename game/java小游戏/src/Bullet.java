import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;

public class Bullet {
	double x,y;
	int speed = 3;
	double degree;
	
	public Bullet(){
		degree = Math.random()*Math.PI*2;
		x = 250;
		y = 250;
	}
	
	public void draw(Graphics g){
		Color c = g.getColor();
		g.setColor(Color.red);
		g.fillOval((int)x, (int)y, 10, 10);
		x += speed*Math.cos(degree);
		y += speed*Math.sin(degree);		
		//使小球反射
		if(y>500-10||y<30){
			degree = -degree;
		}	
		if(x<0||x>500-10){
			degree = Math.PI-degree;
		}
		g.setColor(c);
	}
	
	public Rectangle getRect() {
		Rectangle r = new Rectangle((int)x,(int)y,10,10);
		return r;
	}
}
