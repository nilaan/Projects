import java.awt.event.*; 

import javax.swing.*;

import java.awt.*;
import java.applet.Applet;
public class 2048 extends Applet implements KeyListener{
static int space[][] = new int [3][3];
static JLabel space2[][] = new JLabel[3][3];
static int check[][] = new int [3][3];
JLabel won;
	public 2048() {
		// TODO Auto-generated constructor stub
	}
	public void init()
	{
	resize(400,550);
	setBackground(Color.red);
	setFocusable(true);
	won = new JLabel ("");
	won.setHorizontalAlignment(0);
	for(int i = 0; i<3; i ++)
	{
		for (int j = 0; j < 3; j++)
		{
			space2[i][j] = new JLabel (createImageIcon ("blank.png"));
			add (space2[i][j]);
		}
	}
	addKeyListener(this);
	add (won);
	}

	
	
	 protected static ImageIcon createImageIcon (String path)
	   { //change the red to your class name
	   java.net.URL imgURL = z20482.class.getResource (path);
	   if (imgURL != null)
	   {
	   return new ImageIcon (imgURL);
	   }
	   else
	   {
	   System.err.println ("Couldn't find file: " + path);
	   return null;
	   }
	   }
	 public static void board()
	 {
		 for (int i = 0; i < 3 ; i ++)
		{
			for (int j = 0 ; j < 3 ; j ++)
			{
				if (space[i][j]== 0)
					space2[i][j].setIcon(createImageIcon ("blank.png"));
				else
					space2[i][j].setIcon(createImageIcon (space[i][j]+".png"));
			}
			System.out.println("\n");
		}
	 }
	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		int point = 0;
		for (int o = 0; o<3; o++)
		{
			for (int l = 0; l<3; l++)
			{
				check[o][l]=space[o][l];
			}
		}
		
		if(e.getKeyCode()==37)
		{
		space = moveleft();
		for (int o = 0; o<3; o ++)
		{
			for (int l = 0; l < 3; l++)
			{
				if (space[o][l]==0)
					point++;
			}
		}
		if (point > 0){
		int p = (int) (Math.random() * 3);
		int q = (int) (Math.random() * 3);
		while (space[p][q] != 0) {
			p = (int) (Math.random() * 3);
			q = (int) (Math.random() * 3);
		}
		space[p][q] = 2;}
		else
		{
			won.setText("You lost.");
			removeKeyListener(this);
		}
		}
		if(e.getKeyCode()==39)
		{
			space = moveright();
			for (int o = 0; o<3; o ++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (space[o][l]==0)
						point++;
				}
			}
			if (point > 0){
			int p = (int) (Math.random() * 3);
			int q = (int) (Math.random() * 3);
			while (space[p][q] != 0) {
				p = (int) (Math.random() * 3);
				q = (int) (Math.random() * 3);
			}
			space[p][q] = 2;}
			else
			{
				won.setText("You lost.");
				removeKeyListener(this);
			}
		}
		if(e.getKeyCode()==38)
		{space = moveup();
		for (int o = 0; o<3; o ++)
		{
			for (int l = 0; l < 3; l++)
			{
				if (space[o][l]==0)
					point++;
			}
		}
		if (point > 0){
		int p = (int) (Math.random() * 3);
		int q = (int) (Math.random() * 3);
		while (space[p][q] != 0) {
			p = (int) (Math.random() * 3);
			q = (int) (Math.random() * 3);
		}
		space[p][q] = 2;
		}
		else
		{
			won.setText("You lost.");
			removeKeyListener(this);
		}
		}
		
		if(e.getKeyCode()==40)
		{
			space = movedown();
			for (int o = 0; o<3; o ++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (space[o][l]==0)
						point++;
				}
			}
			if (point > 0){
			int p = (int) (Math.random() * 3);
			int q = (int) (Math.random() * 3);
			while (space[p][q] != 0) {
				p = (int) (Math.random() * 3);
				q = (int) (Math.random() * 3);
			}
			space[p][q] = 2;
		}
			else
				{
				won.setText("You Lost.");
				removeKeyListener(this);
				}
		}
		
		for (int i = 0 ; i < 3 ; i++)
		{
			for (int j = 0; j < 3 ; j++ )
			{
				if (space[i][j]==64)
					won.setText("You have won! You can still continue.");
			}
		}
		board();
	}
	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
	}
	private static int[][] movedown() {
		int point = 0;
		int points = 0;
		for (int i = 1; i >= 0 ; i --)
		{
			for (int j = 2; j >= 0 ; j --)
			{
				if (space[i][j]!=0)
					{point++;
					if(space[i+1][j]!=0 &&space[i+1][j]!=space[i][j])
						points++;
					else if (space[i+1][j]==0)
					{space[i+1][j]=space[i][j];
					space[i][j]=0;}
					else if (space[i+1][j]==space[i][j] && check[i][j]==space[i][j])
					{
						space[i+1][j]*=2;
						space [i][j]=0;
					}
					else if (space[i+1][j]==space[i][j] && check[i][j]!=space[i][j] && check[i][j]!=0)
					{
						points++;
					}
					else if (space[i+1][j]==space[i][j] && check[i][j]!=space[i][j] && check[i][j]==0)
					{
						space[i+1][j]*=2;
						space [i][j]=0;
					}
					}
			}
		}
		if (point == points)
			return space;
		else
			space = movedown();
		return space;
	}

	private static int[][] moveright() {
		int point = 0;
		int points = 0;
		for (int i = 2; i>=0  ; i --)
		{
			for (int j = 1; j >= 0 ; j --)
			{
				if (space[i][j]!=0)
					{point++;
					if(space[i][j+1]!=0 &&space[i][j+1]!=space[i][j])
						points++;
					else if (space[i][j+1]==0)
					{space[i][j+1]=space[i][j];
					space[i][j]=0;}
					else if (space[i][j+1]==space[i][j]&&check[i][j]==space[i][j])
					{
						space[i][j+1]*=2;
						space [i][j]=0;
					}
					else if (space[i][j+1]==space[i][j] && check[i][j]!=space[i][j]&&check[i][j]!=0)
					{
						points++;
					}
					else if (space[i][j+1]==space[i][j] && check[i][j]!=space[i][j]&&check[i][j]==0)
					{
						space[i][j+1]*=2;
						space [i][j]=0;
					}
					}
			}
		}
		if (point == points)
			return space;
		else
			space = moveright();
		return space;
	}

	private static int[][] moveup() {
		int point = 0;
		int points = 0;
		for (int i = 1; i < 3 ; i ++)
		{
			for (int j = 0; j < 3 ; j ++)
			{
				if (space[i][j]!=0)
					{point++;
					if(space[i-1][j]!=0 &&space[i-1][j]!=space[i][j])
						points++;
					else if (space[i-1][j]==0)
					{space[i-1][j]=space[i][j];
					space[i][j]=0;}
					else if (space[i-1][j]==space[i][j]&& check[i][j]==space[i][j])
					{
						space[i-1][j]*=2;
						space [i][j]=0;
					}
					else if (space[i-1][j]==space[i][j] && check[i][j]!=space[i][j]&& check[i][j]!=0)
					{
						points++;
					}
					else if (space[i-1][j]==space[i][j] && check[i][j]!=space[i][j]&& check[i][j]==0)
					{
						space[i-1][j]*=2;
						space [i][j]=0;
					}
					}
			}
		}
		if (point == points)
			return space;
		else
			space = moveup();
		return space;
	}
	private static int[][] moveleft() {
		int point = 0;
		int points = 0;
		for (int i = 0; i < 3 ; i ++)
		{
			for (int j = 1; j < 3 ; j ++)
			{
				if (space[i][j]!=0)
					{point++;
					if(space[i][j-1]!=0 &&space[i][j-1]!=space[i][j])
						points++;
					else if (space[i][j-1]==0)
					{space[i][j-1]=space[i][j];
					space[i][j]=0;}
					else if (space[i][j-1]==space[i][j]&& check[i][j]==space[i][j])
					{
						space[i][j-1]*=2;
						space [i][j]=0;
					}
					else if (space[i][j-1]==space[i][j] && check[i][j]!=space[i][j] && check[i][j]!=0)
					{
						points++;
					}
					else if (space[i][j-1]==space[i][j] && check[i][j]!=space[i][j] && check[i][j]==0)
					{
						space[i][j-1]*=2;
						space [i][j]=0;
					}
					}
			}
		}
		if (point == points)
			return space;
		else
			space = moveleft();
		return space;
	}
	
}
