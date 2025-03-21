package com.testmain.main;

	import nme.display.Sprite;
	import nme.Lib;
	import org.aswing.AbstractButton;
import org.aswing.AbstractCellEditor;
import org.aswing.AbstractListCell;
import org.aswing.AbstractListModel;
import org.aswing.AbstractTabbedPane;
import org.aswing.ASColor;
import org.aswing.ASFont;
import org.aswing.ASFontAdvProperties;
import org.aswing.AssetBackground;
import org.aswing.AssetIcon;
import org.aswing.AssetPane;
import org.aswing.AsWingConstants;
import org.aswing.AsWingManager;
import org.aswing.AsWingUtils;
 
import org.aswing.AWSprite;
import org.aswing.AWTextField;

import org.aswing.border.BevelBorder;
import org.aswing.border.CaveBorder;
import org.aswing.border.DecorateBorder;
import org.aswing.border.EmptyBorder;
import org.aswing.border.LineBorder;
import org.aswing.border.SideLineBorder;
import org.aswing.border.SimpleTitledBorder;
import org.aswing.border.TitledBorder;

import org.aswing.Border;
import org.aswing.BorderLayout;
import org.aswing.BoundedRangeModel;
import org.aswing.Box;
import org.aswing.BoxLayout;
import org.aswing.ButtonGroup;
import org.aswing.ButtonModel;
import org.aswing.Cell;
import org.aswing.CellEditor;
import org.aswing.CellPane;
import org.aswing.CenterLayout;

import org.aswing.colorchooser.AbstractColorChooserPanel;
import org.aswing.colorchooser.ColorRectIcon;
import org.aswing.colorchooser.ColorSelectionModel;
import org.aswing.colorchooser.DefaultColorSelectionModel;
import org.aswing.colorchooser.JColorMixer;
import org.aswing.colorchooser.JColorSwatches;
import org.aswing.colorchooser.NoColorIcon;
import org.aswing.colorchooser.PreviewColorIcon;
import org.aswing.colorchooser.VerticalLayout;

import org.aswing.ComboBoxEditor;
import org.aswing.Component;
import org.aswing.Container;
import org.aswing.ContainerOrderFocusTraversalPolicy;
import org.aswing.Cursor;
import org.aswing.CursorManager;
import org.aswing.Decorator;
import org.aswing.DefaultBoundedRangeModel;
import org.aswing.DefaultButtonModel;
import org.aswing.DefaultCheckBoxCellEditor;
import org.aswing.DefaultComboBoxCellEditor;
import org.aswing.DefaultComboBoxEditor;
import org.aswing.DefaultComboBoxListCell;
import org.aswing.DefaultComboBoxListCellFactory;
import org.aswing.DefaultListCell;
import org.aswing.DefaultListCellFactory;
import org.aswing.DefaultListSelectionModel;
import org.aswing.DefaultListTextCellFactory;
import org.aswing.DefaultNumberTextFieldCellEditor;
import org.aswing.DefaultSingleSelectionModel;
import org.aswing.DefaultTextFieldCellEditor;

import org.aswing.dnd.DefaultDragImage;
import org.aswing.dnd.DirectlyRemoveMotion;
import org.aswing.dnd.DraggingImage;
import org.aswing.dnd.DragListener;
import org.aswing.dnd.DragManager;
import org.aswing.dnd.DropMotion;
import org.aswing.dnd.RejectedMotion;
import org.aswing.dnd.SourceData;

import org.aswing.EditableComponent;
import org.aswing.EmptyFont;
import org.aswing.EmptyIcon;
import org.aswing.EmptyLayout;

import org.aswing.error.AsWingManagerNotInited;
import org.aswing.error.ImpMissError;
import org.aswing.error.UnsupportedError;
import org.aswing.event.AttachEvent;
import org.aswing.event.AWEvent;
import org.aswing.event.CellEditorListener;
import org.aswing.event.ClickCountEvent;
import org.aswing.event.ColorChooserEvent;
import org.aswing.event.ContainerEvent;
import org.aswing.event.DragAndDropEvent;
import org.aswing.event.ExpandVetoException;
import org.aswing.event.FocusKeyEvent;
import org.aswing.event.FrameEvent;
import org.aswing.event.InteractiveEvent;
import org.aswing.event.ListDataEvent;
import org.aswing.event.ListDataListener;
import org.aswing.event.ListItemEvent;
import org.aswing.event.ModelEvent;
import org.aswing.event.MovedEvent;
import org.aswing.event.PopupEvent;
import org.aswing.event.PropertyChangeEvent;
import org.aswing.event.ReleaseEvent;
import org.aswing.event.ResizedEvent;
import org.aswing.event.ScrollPaneEvent;
import org.aswing.event.SelectionEvent;
import org.aswing.event.TabCloseEvent;
import org.aswing.event.TableCellEditEvent;
import org.aswing.event.TableModelEvent;
import org.aswing.event.TableModelListener;
import org.aswing.event.ToolTipEvent;
import org.aswing.event.TreeCellEditEvent;
import org.aswing.event.TreeEvent;
import org.aswing.event.TreeModelEvent;
import org.aswing.event.TreeModelListener;
import org.aswing.event.TreeSelectionEvent;
import org.aswing.event.WindowEvent;


import org.aswing.ext.DateChooser;
import org.aswing.ext.DateGridLayout;
import org.aswing.ext.DateLabel;
import org.aswing.ext.DateRange;
import org.aswing.ext.DefaultGridCell;
import org.aswing.ext.Folder;
import org.aswing.ext.Form;
import org.aswing.ext.FormRow;
import org.aswing.ext.GeneralGridListCellFactory;
import org.aswing.ext.GridCellHolder;
import org.aswing.ext.GridList;
import org.aswing.ext.GridListCell;
import org.aswing.ext.GridListCellFactory;
import org.aswing.ext.GridListItemEvent;
import org.aswing.ext.GridListLayout;
import org.aswing.ext.MultilineLabel;

import org.aswing.FlowLayout;
import org.aswing.FlowWrapLayout;
import org.aswing.FocusManager;
import org.aswing.FocusTraversalPolicy;
import org.aswing.FrameTitleBar;
import org.aswing.FrameTitleBarLayout;
import org.aswing.GeneralListCellFactory;

import org.aswing.geom.IntDimension;
import org.aswing.geom.IntPoint;
import org.aswing.geom.IntRectangle;

import org.aswing.GradientBackground;

import org.aswing.graphics.BitmapBrush;
import org.aswing.graphics.GradientBrush;
import org.aswing.graphics.GradientPen;
import org.aswing.graphics.Graphics2D;
import org.aswing.graphics.IBrush;
import org.aswing.graphics.IPen;
import org.aswing.graphics.Pen;
import org.aswing.graphics.SolidBrush;

import org.aswing.GridLayout;
import org.aswing.GroundDecorator;
import org.aswing.Icon;
import org.aswing.Insets;
import org.aswing.JAccordion;
import org.aswing.JAdjuster;
 
import org.aswing.JButton;
import org.aswing.JCheckBox;
import org.aswing.JCheckBoxMenuItem;
import org.aswing.JClosableTabbedPane;
import org.aswing.JColorChooser;
import org.aswing.JComboBox;
import org.aswing.JFrame;
import org.aswing.JFrameTitleBar;
import org.aswing.JLabel;
import org.aswing.JLabelButton;
import org.aswing.JList;
import org.aswing.JLoadPane;
import org.aswing.JMenu;
import org.aswing.JMenuBar;
import org.aswing.JMenuItem;
import org.aswing.JOptionPane;
import org.aswing.JPanel;
import org.aswing.JPopup;
import org.aswing.JPopupMenu;
import org.aswing.JProgressBar;
import org.aswing.JRadioButton;
import org.aswing.JRadioButtonMenuItem;
import org.aswing.JRootPane;
import org.aswing.JScrollBar;
import org.aswing.JScrollPane;
import org.aswing.JSeparator;
import org.aswing.JSharedToolTip;
import org.aswing.JSlider;
import org.aswing.JSpacer;
import org.aswing.JSplitPane;
import org.aswing.JStepper;
import org.aswing.JTabbedPane;
import org.aswing.JTable;
import org.aswing.JTextArea;
import org.aswing.JTextComponent;
import org.aswing.JTextField;
import org.aswing.JToggleButton;
import org.aswing.JToolBar;
import org.aswing.JToolTip;
import org.aswing.JTree;
import org.aswing.JViewport;
import org.aswing.JWindow;
import org.aswing.KeyboardManager;
import org.aswing.KeyMap;
import org.aswing.KeySequence;
import org.aswing.KeyStroke;
import org.aswing.KeyType;
import org.aswing.LayoutManager;
import org.aswing.ListCell;
import org.aswing.ListCellFactory;
import org.aswing.ListModel;
import org.aswing.ListSelectionModel;
import org.aswing.LoadIcon;
import org.aswing.LookAndFeel;
import org.aswing.MenuElement;
import org.aswing.MenuSelectionManager;
import org.aswing.MultipleAssetIcon;
import org.aswing.MutableListModel;
import org.aswing.Orientable;

import org.aswing.plaf.AdjusterUI;
import org.aswing.plaf.ArrayUIResource;
import org.aswing.plaf.ASColorUIResource;
import org.aswing.plaf.ASFontUIResource;
import org.aswing.plaf.BaseComponentUI;
import org.aswing.plaf.basic.accordion.BasicAccordionHeader;
import org.aswing.plaf.basic.adjuster.PopupSliderThumbIcon;
import org.aswing.plaf.basic.adjuster.PopupSliderUI;
import org.aswing.plaf.basic.background.ButtonBackground;
import org.aswing.plaf.basic.background.ComboBoxBackground;
import org.aswing.plaf.basic.background.FrameBackground;
import org.aswing.plaf.basic.background.InputBackground;
import org.aswing.plaf.basic.background.ListBackground;
import org.aswing.plaf.basic.background.PanelBackground;
import org.aswing.plaf.basic.background.ProgressBarBackground;
import org.aswing.plaf.basic.background.ProgressBarIcon;
import org.aswing.plaf.basic.background.ScrollBarBackground;
import org.aswing.plaf.basic.background.ScrollBarThumb;
import org.aswing.plaf.basic.background.TableBackground;
import org.aswing.plaf.basic.background.TableHeaderBackground;
import org.aswing.plaf.basic.background.TextComponentBackBround;
import org.aswing.plaf.basic.background.ToggleButtonBackground;
import org.aswing.plaf.basic.background.ToolTipBackground;
import org.aswing.plaf.basic.BasicAccordionUI;
import org.aswing.plaf.basic.BasicAdjusterUI;
import org.aswing.plaf.basic.BasicButtonUI;
import org.aswing.plaf.basic.BasicCheckBoxMenuItemUI;
import org.aswing.plaf.basic.BasicCheckBoxUI;
import org.aswing.plaf.basic.BasicClosableTabbedPaneUI;
import org.aswing.plaf.basic.BasicColorChooserUI;
import org.aswing.plaf.basic.BasicColorMixerUI;
import org.aswing.plaf.basic.BasicColorSwatchesUI;
import org.aswing.plaf.basic.BasicComboBoxUI;
import org.aswing.plaf.basic.BasicFrameTitleBarUI;
import org.aswing.plaf.basic.BasicFrameUI;
import org.aswing.plaf.basic.BasicGraphicsUtils;
import org.aswing.plaf.basic.BasicLabelButtonUI;
import org.aswing.plaf.basic.BasicLabelUI;
import org.aswing.plaf.basic.BasicListUI;
import org.aswing.plaf.basic.BasicLookAndFeel;
import org.aswing.plaf.basic.BasicMenuBarUI;
import org.aswing.plaf.basic.BasicMenuItemUI;
import org.aswing.plaf.basic.BasicMenuUI;
import org.aswing.plaf.basic.BasicPanelUI;
import org.aswing.plaf.basic.BasicPopupMenuUI;
import org.aswing.plaf.basic.BasicProgressBarUI;
import org.aswing.plaf.basic.BasicRadioButtonMenuItemUI;
import org.aswing.plaf.basic.BasicRadioButtonUI;
import org.aswing.plaf.basic.BasicScrollBarUI;
import org.aswing.plaf.basic.BasicScrollPaneUI;
import org.aswing.plaf.basic.BasicSeparatorUI;
import org.aswing.plaf.basic.BasicSliderUI;
import org.aswing.plaf.basic.BasicSpacerUI;
import org.aswing.plaf.basic.BasicSplitPaneUI;
import org.aswing.plaf.basic.BasicStepperUI;
import org.aswing.plaf.basic.BasicTabbedPaneUI;
import org.aswing.plaf.basic.BasicTableHeaderUI;
import org.aswing.plaf.basic.BasicTableUI;
import org.aswing.plaf.basic.BasicTextAreaUI;
import org.aswing.plaf.basic.BasicTextComponentUI;
import org.aswing.plaf.basic.BasicTextFieldUI;
import org.aswing.plaf.basic.BasicToggleButtonUI;
import org.aswing.plaf.basic.BasicToolBarUI;
import org.aswing.plaf.basic.BasicToolTipUI;
import org.aswing.plaf.basic.BasicTreeUI;
import org.aswing.plaf.basic.BasicViewportUI;
import org.aswing.plaf.basic.border.ColorChooserBorder;
import org.aswing.plaf.basic.border.ComboBoxBorder;
import org.aswing.plaf.basic.border.ComboBoxPopupBorder;
import org.aswing.plaf.basic.border.EmptyBorderResource;
import org.aswing.plaf.basic.border.FrameBorder;
import org.aswing.plaf.basic.border.PopupMenuBorder;
import org.aswing.plaf.basic.border.ProgressBarBorder;
import org.aswing.plaf.basic.border.TableHeaderCellBorder;
import org.aswing.plaf.basic.border.TextAreaBorder;
import org.aswing.plaf.basic.border.TextComponentBorder;
import org.aswing.plaf.basic.border.TextFieldBorder;
import org.aswing.plaf.basic.border.ToolTipBorder;
import org.aswing.plaf.basic.cursor.H_ResizeCursor;
import org.aswing.plaf.basic.cursor.HV_ResizeCursor;
import org.aswing.plaf.basic.cursor.V_ResizeCursor;
import org.aswing.plaf.basic.DefaultMenuLayout;
import org.aswing.plaf.basic.frame.BasicFrameTitleBarBG;
import org.aswing.plaf.basic.icon.ArrowIcon;
import org.aswing.plaf.basic.icon.CheckBoxIcon;
import org.aswing.plaf.basic.icon.CheckBoxMenuItemCheckIcon;
import org.aswing.plaf.basic.icon.FrameCloseIcon;
import org.aswing.plaf.basic.icon.FrameIcon;
import org.aswing.plaf.basic.icon.FrameIconifiedIcon;
import org.aswing.plaf.basic.icon.FrameMaximizeIcon;
import org.aswing.plaf.basic.icon.FrameNormalIcon;
import org.aswing.plaf.basic.icon.MenuArrowIcon;
import org.aswing.plaf.basic.icon.MenuCheckIcon;
import org.aswing.plaf.basic.icon.MenuItemArrowIcon;
import org.aswing.plaf.basic.icon.MenuItemCheckIcon;
import org.aswing.plaf.basic.icon.RadioButtonIcon;
import org.aswing.plaf.basic.icon.RadioButtonMenuItemCheckIcon;
import org.aswing.plaf.basic.icon.ScrollBarArrowIcon;
import org.aswing.plaf.basic.icon.SliderThumbIcon;
import org.aswing.plaf.basic.icon.SolidArrowIcon;
import org.aswing.plaf.basic.icon.TitleIcon;
import org.aswing.plaf.basic.splitpane.Divider;
import org.aswing.plaf.basic.splitpane.DividerIcon;
import org.aswing.plaf.basic.tabbedpane.BasicClosableTabbedPaneTab;
import org.aswing.plaf.basic.tabbedpane.BasicTabbedPaneTab;
import org.aswing.plaf.basic.tabbedpane.ClosableTab;
import org.aswing.plaf.basic.tabbedpane.CloseIcon;
import org.aswing.plaf.basic.tabbedpane.Tab;
import org.aswing.plaf.basic.tabbedpane.TabBackground;
import org.aswing.plaf.basic.tree.BasicExpandControl;
import org.aswing.plaf.basic.tree.ExpandControl;

import org.aswing.plaf.ColorSwatchesUI;
import org.aswing.plaf.ComboBoxUI;
import org.aswing.plaf.ComponentUI;
import org.aswing.plaf.DefaultEmptyDecoraterResource;
import org.aswing.plaf.DefaultsDecorator;
import org.aswing.plaf.DefaultsDecoratorBase;
import org.aswing.plaf.EmptyLayoutUIResourse;
import org.aswing.plaf.EmptyUIResources;
import org.aswing.plaf.FrameUI;
import org.aswing.plaf.InsetsUIResource;
import org.aswing.plaf.MenuElementUI;
import org.aswing.plaf.SliderUI;
import org.aswing.plaf.SplitPaneUI;
import org.aswing.plaf.TableUI;
import org.aswing.plaf.TreeUI;
import org.aswing.plaf.UIResource;
import org.aswing.plaf.UIStyleTune;

import org.aswing.RepaintManager;

import org.aswing.resizer.DefaultResizeBarHandler;
import org.aswing.resizer.DefaultResizer;
import org.aswing.resizer.Resizer;
import org.aswing.resizer.ResizerController;
import org.aswing.resizer.ResizeStrategy;
import org.aswing.resizer.ResizeStrategyImp;

import org.aswing.ScrollPaneLayout;
import org.aswing.SimpleButtonIcon;
import org.aswing.SimpleButtonIconToggle;
import org.aswing.SingleSelectionModel;
import org.aswing.SoftBox;
import org.aswing.SoftBoxLayout;
import org.aswing.SolidBackground;
import org.aswing.StyleResult;
import org.aswing.StyleTune;

import org.aswing.table.AbstractTableCell;
import org.aswing.table.AbstractTableModel;
import org.aswing.table.DefaultTableColumnModel;
import org.aswing.table.DefaultTableModel;
import org.aswing.table.DefaultTextCell;
import org.aswing.table.DefaultTextHeaderCell;
import org.aswing.table.GeneralTableCellFactory;
import org.aswing.table.GeneralTableCellFactoryUIResource;
import org.aswing.table.JTableHeader;
import org.aswing.table.PoorTextCell;
import org.aswing.table.PropertyTableModel;
import org.aswing.table.PropertyTranslator;
import org.aswing.table.Resizable2;
import org.aswing.table.Resizable2Imp1;
import org.aswing.table.Resizable3;
import org.aswing.table.Resizable3Imp1;
import org.aswing.table.Resizable3Imp2;
import org.aswing.table.SelectablePoorTextCell;
import org.aswing.table.sorter.Arrow;
import org.aswing.table.sorter.Directive;
import org.aswing.table.sorter.Row;
import org.aswing.table.sorter.SortableHeaderRenderer;
import org.aswing.table.sorter.SortableTextHeaderCell;
import org.aswing.table.sorter.TableSorter;
import org.aswing.table.TableCell;
import org.aswing.table.TableCellEditor;
import org.aswing.table.TableCellFactory;
import org.aswing.table.TableColumn;
import org.aswing.table.TableColumnModel;
import org.aswing.table.TableColumnModelEvent;
import org.aswing.table.TableColumnModelListener;
import org.aswing.table.TableModel;

import org.aswing.ToggleButtonModel;

import org.aswing.tree.AbstractLayoutCache;
import org.aswing.tree.DefaultMutableTreeNode;
import org.aswing.tree.DefaultTreeCell;
import org.aswing.tree.DefaultTreeModel;
import org.aswing.tree.DefaultTreeSelectionModel;
import org.aswing.tree.EmptySelectionModel;
import org.aswing.tree.EnumerationInfo;
import org.aswing.tree.FHTreeStateNode;
import org.aswing.tree.FixedHeightLayoutCache;
import org.aswing.tree.GeneralTreeCellFactory;
import org.aswing.tree.GeneralTreeCellFactoryUIResource;
import org.aswing.tree.MutableTreeNode;
import org.aswing.tree.NodeDimensions;
import org.aswing.tree.PathPlaceHolder;
import org.aswing.tree.RowMapper;
import org.aswing.tree.SearchInfo;
import org.aswing.tree.TreeCell;
import org.aswing.tree.TreeCellEditor;
import org.aswing.tree.TreeCellFactory;
import org.aswing.tree.TreeFolderIcon;
import org.aswing.tree.TreeLeafIcon;
import org.aswing.tree.TreeModel;
import org.aswing.tree.TreeNode;
import org.aswing.tree.TreePath;
import org.aswing.tree.TreePathMap;
import org.aswing.tree.TreeSelectionModel;

import org.aswing.UIDefaults;
import org.aswing.UIManager;

import org.aswing.util.AbstractImpulser;
import org.aswing.util.ArrayList;
import org.aswing.util.ArrayUtils;
import org.aswing.util.DepthManager;
import org.aswing.util.HashMap;
import org.aswing.util.HashSet;
import org.aswing.util.Impulser;
import org.aswing.util.LinkedList;
import org.aswing.util.List;
import org.aswing.util.ListNode;
import org.aswing.util.ObjectUtils;
import org.aswing.util.Reflection;
import org.aswing.util.Stack;
import org.aswing.util.StringUtils;
import org.aswing.util.Timer;
import org.aswing.util.WeakMap;
import org.aswing.util.WeakReference;

import org.aswing.VectorListModel;
import org.aswing.Viewportable;
import org.aswing.ViewportLayout;
import org.aswing.WeightBoxLayout;
import org.aswing.WindowLayout;
import org.aswing.WindowOrderFocusTraversalPolicy;
/*
class TestMain 
{

    static public function main()
    {
        //#if flash
        new TestMain();
        //#else 
        //Lib.create(function(){new Main();},800,600,60,0xccccff,(1*Lib.HARDWARE) | Lib.RESIZABLE, "AsWing_Paling_UI");
        //
        //#end

    }

    public  function new():Void
    {  
        AsWingManager.initAsStandard( Lib.current);

        var sp:org.aswing.JLabel= new  org.aswing.JLabel("*****sdew中文");

        sp.setSizeWH(100, 30);
        sp.setLocationXY(10, 10);
        Lib.current.addChild(sp);
        var jb:JButton = new JButton("__ewwesew中文");
        jb.setSizeWH(100, 20);
        jb.setLocationXY(300, 300);

        Lib.current.addChild(jb);
        var tt : JFrame = new JFrame( Lib.current,"TestAswing中文");

        tt.setSizeWH(300,300);
        tt.setLocationXY(100,100);
        tt.show(); 
    }
}
*/

import nme.display.Sprite;

import nme.display.Stage;
import nme.display.StageAlign;
import nme.display.StageScaleMode;
import nme.Lib;
import nme.text.TextField;
import base.conf.Config;
import base.state.StateMachine;
import com.ac.state.InitACState;


#if flash
import base.common.FlashConnect;
#end

class TestMain extends Sprite {

    static public function main()
    {
#if flash FlashConnect.redirect(); #end
        Lib.current.addChild (new TestMain());
    }

    public function new () {

        super ();
        initialize ();
    }

    private function initialize ():Void {
        Lib.current.stage.align = StageAlign.TOP_LEFT;
        Lib.current.stage.scaleMode = StageScaleMode.NO_SCALE;

        Config.ScaleX = Lib.current.stage.stageWidth / 480;
        Config.ScaleY = Lib.current.stage.stageHeight / 320;

        Config.confFileName = "qbox.xml";
        Config.appName = "Qbox";
        var is= new InitACState();
        is.init(StateMachine.getInst());
    }
}

