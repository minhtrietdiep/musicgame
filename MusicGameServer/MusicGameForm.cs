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
        private const int connectionSpeed = 115200;
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
            //UpdateUserInterface();
        }

        private void FillSerialPortSelectionBoxWithAvailablePorts()
        {
            String[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);

            //serialPortSelectionBox.Items.Clear();
            /*foreach (String port in ports)
            {
                serialPortSelectionBox.Items.Add(port);
            }*/
        }

        private void MessageReceived(String message)
        {
            if ((message.Contains(">BTN:")) && message.EndsWith(";"))
            {
                MessageBox.Show("Je hebt knop " + message.Substring(message.IndexOf(":") + 1, message.IndexOf(";") - (message.IndexOf(":") + 1)) + " ingedrukt.");
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

        private void messageReceiveTimer_Tick(object sender, EventArgs e)
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

        private void ProcessMessages()
        {
            String message = messageBuilder.FindAndRemoveNextMessage();
            while (message != null)
            {
                //DisplayReceivedMessage(message);
                MessageReceived(message);
                message = messageBuilder.FindAndRemoveNextMessage();
            }
        }

        private void MusicGameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            readMessageTimer.Enabled = false;
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

    }
}
