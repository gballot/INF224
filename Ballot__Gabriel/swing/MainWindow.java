import java.awt.*;
import java.awt.event.ActionEvent;
import javax.swing.*;
import javax.swing.text.*;

public class MainWindow extends JFrame{
	//Class version
	private static final long serialVersionUID = 1L;
	//Components of the main window
	private JButton allMediasButton1 = new JButton(new AddTextListener("All Medias", this));
	private JButton allGroupsButton1 = new JButton(new AddTextListener("All Groups", this));
	private JButton searchMediaButton1 = new JButton(new AddTextListener("Search Media", this));
	private JButton searchGroupButton1 = new JButton(new AddTextListener("Search Group", this));
	private JButton quitButton1 = new JButton(new CloseListener("Quit"));
	private JButton allMediasButton2 = new JButton(new AddTextListener("All Medias", this));
	private JButton allGroupsButton2 = new JButton(new AddTextListener("All Groups", this));
	private JButton searchMediaButton2 = new JButton(new AddTextListener("Search Media", this));
	private JButton searchGroupButton2 = new JButton(new AddTextListener("Search Group", this));

	private JTextPane textpane = new JTextPane();
	private JScrollPane scroll = new JScrollPane(textpane);
	private JMenuBar menubar = new JMenuBar();
	private JMenu mainMenu = new JMenu("Menu");
	private JMenu createMenu = new JMenu("Create");
	private JMenu searchMenu = new JMenu("Search");
	private JMenu deleteMenu = new JMenu("Delete");
	private JToolBar toolbar = new JToolBar("Tool bar");
	
	private JMenuItem quitItem = new JMenuItem(new CloseListener("Quit"));
	private JMenuItem addMediaToGroupItem = new JMenuItem(new AddTextListener("Add a Media to a Group", this));
	private JMenuItem openMediaItem = new JMenuItem(new AddTextListener("Open a media", this));
	
	private JMenuItem createVideoItem = new JMenuItem(new AddTextListener("Video", this));
	private JMenuItem createPhotoItem = new JMenuItem(new AddTextListener("Photo", this));
	private JMenuItem createFilmItem = new JMenuItem(new AddTextListener("Film", this));
	private JMenuItem createGroupItem = new JMenuItem(new AddTextListener("Group", this));
	
	private JMenuItem searchMediaItem = new JMenuItem(new AddTextListener("Media", this));
	private JMenuItem searchGroupItem  = new JMenuItem(new AddTextListener("Group", this));
	private JMenuItem allMediaItem = new JMenuItem(new AddTextListener("All Medias", this));
	private JMenuItem allGroupItem = new JMenuItem(new AddTextListener("All Groups", this));
	
	private JMenuItem deleteMediaItem = new JMenuItem(new AddTextListener("Media", this));
	private JMenuItem deleteGroupItem  = new JMenuItem(new AddTextListener("Group", this));
	
	private Client client;
	
	public MainWindow(Client client) {
		this.client = client;
		//Disable Apple GUI look
		try {
		    UIManager.setLookAndFeel( UIManager.getCrossPlatformLookAndFeelClassName() );
		 } catch (Exception e) {
		            e.printStackTrace();
		 }
		System.setProperty("apple.laf.useScreenMenuBar", "true");
		
		//Design of buttons
		allMediasButton1.setBackground(Color.lightGray);
		allMediasButton1.setOpaque(true);
		allGroupsButton1.setBackground(Color.lightGray);
		allGroupsButton1.setOpaque(true);
		searchMediaButton1.setBackground(Color.lightGray);
		searchMediaButton1.setOpaque(true);
		searchGroupButton1.setBackground(Color.lightGray);
		searchGroupButton1.setOpaque(true);
		quitButton1.setBackground(Color.darkGray);
		quitButton1.setForeground(Color.lightGray);
		quitButton1.setOpaque(true);
		allMediasButton2.setBackground(Color.lightGray);
		allMediasButton2.setOpaque(true);
		allGroupsButton2.setBackground(Color.lightGray);
		allGroupsButton2.setOpaque(true);
		searchMediaButton2.setBackground(Color.lightGray);
		searchMediaButton2.setOpaque(true);
		searchGroupButton2.setBackground(Color.lightGray);
		searchGroupButton2.setOpaque(true);

		//Menus Layout
		mainMenu.add(openMediaItem);
		mainMenu.add(addMediaToGroupItem);
		mainMenu.add(quitItem);
		
		createMenu.add(createPhotoItem);
		createMenu.add(createVideoItem);
		createMenu.add(createFilmItem);
		createMenu.add(createGroupItem);
		
		searchMenu.add(searchMediaItem);
		searchMenu.add(searchGroupItem);
		searchMenu.add(allMediaItem);
		searchMenu.add(allGroupItem);
		
		deleteMenu.add(deleteMediaItem);
		deleteMenu.add(deleteGroupItem);

		menubar.add(mainMenu);
		menubar.add(createMenu);
		menubar.add(searchMenu);
		menubar.add(deleteMenu);
		setJMenuBar(menubar);
		
        //TextPane
        textpane.setPreferredSize(new Dimension(800, 800));
        textpane.setEditable(false);
        String intro = "Wellcome in the Java remote !\n\n"+
            "You can send requests to the C++ server"+
            "The requests and the responses will be printed"+
            "below. Then you will see the responses from the"+
            "server. They will be printed as raw text."+
            "to fully understand the meaning of this respnoses"+
            "you can check out the protocole.md file. The responses"+
            "for the searches of medias are withe this format :\n\n"+
            "    <name> <path> <media type> <info>\n\n"+
            "where <info> depends on the media type :\n"+
            "* photo : <info> = <latitude> <longitude>\n"+
            "* video : <info> = <length>\n"+
            "* film : <info> = <nb_chapters> <length chap 1> <length chap 2> etc...\n\n"+
            "Moreover, as a film is a video, there will be \"video <length>\" before \"film\"\n\n\n";
        addColoredText(textpane, intro, Color.lightGray);

		//ToolBar layout
		toolbar.add(allMediasButton2);
		toolbar.add(allGroupsButton2);
		toolbar.add(searchMediaButton2);
		toolbar.add(searchGroupButton2);
		
		//BorderLayout
		JPanel buttonContainer = new JPanel();
		JPanel toolBarContainer = new JPanel();
		buttonContainer.setLayout(new GridLayout(1,5));
		buttonContainer.add(allMediasButton1);
		buttonContainer.add(allGroupsButton1);
		buttonContainer.add(searchMediaButton1);
		buttonContainer.add(searchGroupButton1);
		buttonContainer.add(quitButton1);
		toolBarContainer.add(toolbar);
		buttonContainer.setPreferredSize(new Dimension(30,30));
		add(scroll, BorderLayout.CENTER);
		add(buttonContainer, BorderLayout.SOUTH);
		add(toolBarContainer, BorderLayout.NORTH);
				
		//Display main window
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);			
	}
	
	public void displayRequest(String text) {
        addColoredText(textpane, "Request : ", Color.GRAY);
        addColoredText(textpane, text + "\n", Color.BLACK);
	}

	public void displayResponse(String text) {
        addColoredText(textpane, "Response : ", Color.GREEN);
        addColoredText(textpane, text + "\n", Color.BLACK);
	}
	
	public void displayError(String text) {
        addColoredText(textpane, "ERROR : ", Color.RED);
        addColoredText(textpane, text + "\n", Color.BLACK);
	}

	public void displayInfo(String text) {
        addColoredText(textpane, "INFO : ", Color.CYAN);
        addColoredText(textpane, text + "\n", Color.BLACK);
	}

    public void addColoredText(JTextPane pane, String text, Color color) {
                StyledDocument doc = pane.getStyledDocument();

                        Style style = pane.addStyle("Color Style", null);
                                StyleConstants.setForeground(style, color);
                                try {
                                                doc.insertString(doc.getLength(), text, style);
                                                        
                                } 
                                catch (BadLocationException e) {
                                                e.printStackTrace();
                                                        
                                }           
                                    
    }
	
	
	//Quit Button Listener
	class CloseListener extends AbstractAction {
		public CloseListener(String texte) {
			super(texte);
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			int n = JOptionPane.showConfirmDialog(null, "Are you sure you want to quit ?", "Quit", JOptionPane.YES_NO_OPTION);
			switch(n) {
			case 0 :
				System.exit(0);;
			case 1 :
			}
		}
	}
	
	//Communication protocol for client
	class AddTextListener extends AbstractAction {
		private MainWindow window;
		public AddTextListener(String texte, MainWindow window) {
			super(texte);
			this.window = window;
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			String request = null;
			String man[];
			//All Medias
			if (arg0.getSource() == allMediasButton1 || arg0.getSource() == allMediasButton2 || arg0.getSource() == allMediaItem) {
				request = "get allmedias";
				window.displayRequest(request);
				String response = client.send(request);
                if(response.equals("fail")) {
                    window.displayError("Fail");
                } else if(response.equals("")) {
                    window.displayInfo("Sorry there is no media in the data base yet... Use \"create > media\" to create one !");
                } else {
                    window.displayResponse(response);
                }	
            }
            //All Groups
            else if (arg0.getSource() == allGroupItem || arg0.getSource() == allGroupsButton1 || arg0.getSource() == allGroupsButton2) {
                request = "get allgroups";
                window.displayRequest(request);
                String response = client.send(request);
                if(response.equals("fail")) {
			    		window.displayError("Fail");
                } else if(response.equals("")) {
                    window.displayInfo("Sorry there is no goup in the data base yet... Use \"create > group\" to create one !");
                } else {
                    window.displayResponse(response);
			    }
			}
			//Create a photo
			else if (arg0.getSource() == createPhotoItem) {
				request = "create photo ";
				man = new String[]{"name", "paht", "latitude", "longitude"};
				new RequestWindow(request,man,client,window);
			}
			//Create a video
			else if (arg0.getSource() == createVideoItem) {
				request = "create video ";
				man = new String[]{"name", "paht", "length"};
				new RequestWindow(request,man,client,window);
			}
			//Create a film
			else if (arg0.getSource() == createFilmItem) {
				request = "create film ";
				man = new String[]{"name", "paht", "length (optionnal)", "number of chapters", "length chapters (list of intergers separated with spaces)"};
				new RequestWindow(request,man,client,window);
			}
			//Create a group
			else if (arg0.getSource() == createGroupItem) {
				request = "create group ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Open a media
			else if (arg0.getSource() == openMediaItem) {
				request = "open ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Search a media
			else if (arg0.getSource() == searchMediaItem || arg0.getSource() == searchMediaButton1 || arg0.getSource() == searchMediaButton2) {
				request = "get media ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Search a group
			else if (arg0.getSource() == searchGroupItem || arg0.getSource() == searchGroupButton1 || arg0.getSource() == searchGroupButton2) {
				request = "get group ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Delete a Media
			else if (arg0.getSource() == deleteMediaItem) {
				request = "delete media ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Delete a Group
			else if (arg0.getSource() == deleteGroupItem) {
				request = "delete group ";
				man = new String[]{"name"};
				new RequestWindow(request,man,client,window);
			}
			//Add a media to a group
			else if (arg0.getSource() == addMediaToGroupItem) {
				request = "add ";
				man = new String[]{"group name", "media name"};
				new RequestWindow(request,man,client,window);
			}
			
		}
		
	}
	
}
