using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace LCD_Tester_v1._0
{
    public partial class Form1 : Form
    {
        string[] ports = SerialPort.GetPortNames();
        string RxString;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.ResetText();
            foreach(string port in ports)
            comboBox1.Items.Add(port);
            if (ports.Count() != 0)
            comboBox1.SelectedIndex = 0;
            serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
        }

        private void Connect_button_Click(object sender, EventArgs e)
        {
             if (serialPort.IsOpen)
            {
                serialPort.Close();
                Connect_button.Text = "Connect";
                status.Text = "Disconnected";
                comboBox1.Enabled = true;
                button2.Enabled = true;                
            }
            else if (!serialPort.IsOpen)
            {
                
                 try
                {
                    serialPort.PortName = ports[comboBox1.SelectedIndex];
                    serialPort.Open();
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message);
                }
                if (serialPort.IsOpen)
                {
                    richTextBox1.Clear();
                    Connect_button.Text = "Disconnect";
                    status.Text = "Connected";
                    comboBox1.Enabled = false;
                    button2.Enabled = false;
                 }
            }
        }

        private void Send_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write(textBox1.Text);
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");

        }

        private void mode4_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("mode=4");
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");

        }

        private void mode8_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("mode=8");
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");

        }

        private void Auto_on_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
                {
                  serialPort.Write("mode=A");
                  serialPort.Write(new byte[] {0x0d} ,0 ,1);
                 }
            else
                MessageBox.Show("COM Port Error");
        }

        private void Auto_off_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("amode off");
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");
        }

        private void lcd_1_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("lcd.1 " + textBox1.Text);
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");
        }
 
        private void lcd_2_button_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("lcd.2 " + textBox1.Text);
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
            }
            else
                MessageBox.Show("COM Port Error");
         }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            RxString = serialPort.ReadExisting();
            this.Invoke(new EventHandler(DisplayText));
        }
        private void DisplayText(object sender, EventArgs e)
        {
            richTextBox1.AppendText(RxString);
        }

        private void clear_button_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
        }

         private void button1_Click(object sender, EventArgs e)
        {
            if(serialPort.IsOpen)
            {
                serialPort.Write("ctime " +  DateTime.Now.ToString("HH:mm:ss"));
                serialPort.Write(new byte[] {0x0d} ,0 ,1);
                System.Threading.Thread.Sleep(700);
                serialPort.Write("cDate " + DateTime.Now.ToString("dd:MM:yyyy"));
                serialPort.Write(new byte[] { 0x0d }, 0, 1);
            }
            else
                MessageBox.Show("COM Port Error");
        }
        private void button2_Click(object sender, EventArgs e)
        {
            comboBox1.ResetText();
            comboBox1.Items.Clear();
            ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            comboBox1.Items.Add(port);
            if (ports.Count() != 0)
            comboBox1.SelectedIndex = 0;
           
        }

        private void time_date_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write("ctime?");
                serialPort.Write(new byte[] { 0x0d }, 0, 1);
                System.Threading.Thread.Sleep(1000);
                serialPort.Write("cdate?");
                serialPort.Write(new byte[] { 0x0d }, 0, 1);
            }
            else
                MessageBox.Show("COM Port Error");
        }
    }
}
