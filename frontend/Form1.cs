using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Octoduino_FrontEnd
{
    public partial class Form1 : Form
    {
        SerialPort arduinoBoard = new SerialPort();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void textBox1_Leave(object sender, EventArgs e)
        {
            webBrowser1.Url = new Uri(textBox1.Text);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!arduinoBoard.IsOpen)
            {
                arduinoBoard.DataReceived += updateSerial;
                if (comboBox1.SelectedText == "")
                {
                    arduinoBoard.PortName = "COM1";
                    if(checkBox1.Checked)
                    {
                        firmataVB1.COMPortName = "COM1";
                    }
                }
                if(checkBox1.Checked)
                {
                    firmataVB1.Baud = Convert.ToInt32(textBox1.Text);
                }
                else
                {
                    arduinoBoard.PortName = comboBox1.SelectedText;
                }
                try
                {
                    arduinoBoard.Open();
                    writeSerial("Connected to device on " + arduinoBoard.PortName + ".");
                }
                catch(System.IO.IOException)
                {
                    //MessageBox.Show("There is no device on " + arduinoBoard.PortName + ".", "COM Error");
                    writeSerial("Connection to device on " + arduinoBoard.PortName + " failed.");
                }
            }
            else
            {
                throw new InvalidOperationException("The Serial Port is already open!");
            }
        }
        private void updateSerial(object sender, SerialDataReceivedEventArgs e)
        {
            string data = arduinoBoard.ReadTo("\x03");
            writeSerial(data);
        }
        private void writeSerial(string data)
        {
            listBox1.Items.Add(getTimestamp() + data);
        }
        private string getTimestamp()
        {
            string stamp = "";
            stamp = "[" + DateTime.Now.Month + "/" + DateTime.Now.Day + " " + DateTime.Now.Hour + ":" + DateTime.Now.Minute + ":" + DateTime.Now.Second + "] ";
            return stamp;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if(arduinoBoard.IsOpen)
            {
                arduinoBoard.Close();
            }
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            writeSerial("Octoduino frontend started.");
        }
    }
}
