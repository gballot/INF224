import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class RequestWindow extends JFrame {
  private JPanel container = new JPanel();
  private JTextField jtf = new JTextField("Request");
  private JLabel label = new JLabel();
  private JButton b = new JButton ("OK");
  private Client client;
  private MainWindow window;

  public RequestWindow(String request, String man, Client client, MainWindow window){
	this.client = client;
	this.window = window;
    this.setTitle("Request to C++ server");
    this.setSize(300, 100);
    this.setLocationRelativeTo(null);
    container.setLayout(new BorderLayout());
    JPanel top = new JPanel();        
    Font police = new Font("Arial", Font.BOLD, 14);
    jtf.setFont(police);
    jtf.setPreferredSize(new Dimension(200, 30));
    jtf.setForeground(Color.BLUE);
    label.setText(man);
    b.addActionListener(new BoutonListener(request, client, window, this));
    top.add(label);
    top.add(jtf);
    top.add(b);
    this.setContentPane(top);
    this.setVisible(true);            
  }       

  class BoutonListener extends AbstractAction{
	private String request;
	private Client client;
	private MainWindow window;
	private RequestWindow rwindow;
	
	public BoutonListener(String request, Client client, MainWindow window, RequestWindow rwindow) {
		super();
		this.request = request;
		this.client = client;
		this.window = window;
		this.rwindow = rwindow;
	}
    public void actionPerformed(ActionEvent e) {
    	request = request + jtf.getText();
    	this.rwindow.dispose();
    	String response = client.send(request);
    	window.displayRequest(request);
	    if(response == "fail") {
	    		window.displayError("Fail, please check that you have correctly entered the request");
	    }
	    else {
            response = response;
	    		window.displayResponse(response);
	    }
    }
  }
}
