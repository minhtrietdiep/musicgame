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

namespace MusicGameServer
{
    public partial class MusicGameForm : Form
    {
        private const int connectionSpeed = 38400;
        private const String messageBeginMarker = ">";
        private const String messageEndMarker = ";";
        private SerialPort serialPort;
        private MessageBuilder messageBuilder;

        public MusicGameForm()
        {
            InitializeComponent();
            FillSerialPortSelectionBoxWithAvailablePorts();

            serialPort = new SerialPort();
            serialPort.BaudRate = connectionSpeed;
            messageBuilder = new MessageBuilder(messageBeginMarker, messageEndMarker);
            UpdateInterface();
        }

        private void FillSerialPortSelectionBoxWithAvailablePorts()
        {
            String[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);

            comboBoxPorts.Items.Clear();
            foreach (String port in ports)
            {
                comboBoxPorts.Items.Add(port);
            }
        }

        private void MessageReceived(String message)
        {
            int subbegin;
            int subend;
            string substring;
            /*if ((message.Contains(">BTN")) && message.EndsWith(";"))
            {
                if ((message.Substring(message.IndexOf("N") + 1, message.IndexOf(";") - (message.IndexOf("N") + 1))) == "10")
                {
                    lblStatus.Text = "depressed";
                }
                else
                {
                    lblStatus.Text = "pressed";
                }
                //MessageBox.Show("Je hebt knop " + message.Substring(message.IndexOf("N") + 1, message.IndexOf(";") - (message.IndexOf("N") + 1)) + " ingedrukt.");
            }*/
            if ((message.Contains(">SCOR")) && message.EndsWith(";"))
            {
                subbegin = message.IndexOf(">") + 5;
                subend = message.IndexOf(";");
                substring = message.Substring(subbegin, subend - subbegin);
                lblScore.Text = "Score: " + substring + "!";
            }
        }

        private bool SendMessage(String message)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write(message);
                    //DisplaySendMessage(message);
                    return true;
                }
                catch (Exception exception) // Not very nice to catch Exception...but for now it's good enough.
                {
                    //Debug.WriteLine("Could not write to serial port: " + exception.Message);
                }
            }
            return false;
        }

        private void readMessageTimer_Tick(object sender, EventArgs e)
        {
            if (serialPort.IsOpen
               && serialPort.BytesToRead > 0)
            {
                try
                {
                    String dataFromSocket = serialPort.ReadExisting();
                    //DisplayReceivedRawData(dataFromSocket);
                    messageBuilder.Append(dataFromSocket);
                    ProcessMessages();
                }
                catch (Exception exception) // Not very nice to catch Exception...but for now it's good enough.
                {
                    //Debug.WriteLine("Could not read from serial port: " + exception.Message);
                }
            }
        }

        /*private void messageReceiveTimer_Tick(object sender, EventArgs e)
        {
            if (serialPort.IsOpen
                && serialPort.BytesToRead > 0)
            {
                try
                {
                    String dataFromSocket = serialPort.ReadExisting();
                    //DisplayReceivedRawData(dataFromSocket);
                    messageBuilder.Append(dataFromSocket);
                    ProcessMessages();
                }
                catch (Exception exception) // Not very nice to catch Exception...but for now it's good enough.
                {
                    //Debug.WriteLine("Could not read from serial port: " + exception.Message);
                }
            }
        }*/

        private void ProcessMessages()
        {
            String message = messageBuilder.FindAndRemoveNextMessage();
            while (message != null)
            {
                DisplayReceivedMessage(message);
                MessageReceived(message);
                message = messageBuilder.FindAndRemoveNextMessage();
            }
        }

        private void DisplayReceivedMessage(String message)
        {
            tbCurrentMsg.Text = message;
        }

        private void MusicGameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            readMessageTimer.Enabled = false;
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            SendMessage(messageBeginMarker + "STRT" + messageEndMarker);
        }

        private void btnGameOver_Click(object sender, EventArgs e)
        {
            SendMessage(messageBeginMarker + "GOVR" + messageEndMarker);
        }

        private void btnCreateSong_Click(object sender, EventArgs e)
        {
            SendMessage(messageBeginMarker + "CRTS" + messageEndMarker);
        }

        private void setSelectSong_Click(object sender, EventArgs e)
        {
            SendMessage(messageBeginMarker + "SLTS" + messageEndMarker);
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            lblScore.Text = "Score: ";
            SendMessage(messageBeginMarker + "RSTC" + messageEndMarker);
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                readMessageTimer.Enabled = false;
                serialPort.Close();
            }
            else
            {
                String port = comboBoxPorts.Text;
                try
                {
                    serialPort.PortName = port;
                    serialPort.Open();
                    if (serialPort.IsOpen)
                    {
                        //ClearAllMessageData();
                        serialPort.DiscardInBuffer();
                        serialPort.DiscardOutBuffer();
                    }
                    readMessageTimer.Enabled = true;
                }
                catch (Exception exception)
                {
                    MessageBox.Show("Could not connect to the given serial port: " + exception.Message);
                }
            }
            UpdateInterface();
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            FillSerialPortSelectionBoxWithAvailablePorts();
            UpdateInterface();
        }

        private void UpdateInterface()
        {
            bool isConnected = serialPort.IsOpen;
            if (isConnected)
            {
                btnConnect.Text = "Disconnect";
            }
            else
            {
                btnConnect.Text = "Connect";
            }

            btnRefresh.Enabled = !isConnected;
            comboBoxPorts.Enabled = !isConnected;

            btnStart.Enabled = isConnected;
            btnReset.Enabled = isConnected;
            btnGameOver.Enabled = isConnected;
            btnStart.Enabled = isConnected;
            btnCreateSong.Enabled = isConnected;
            setSelectSong.Enabled = isConnected;
            comboBoxMusic.Enabled = isConnected;
        }
    }
}
