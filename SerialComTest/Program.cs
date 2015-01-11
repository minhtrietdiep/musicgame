using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;

namespace SerialComTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort port = new SerialPort("COM7");
            port.BaudRate = 38400;

            port.Open();

            string buffer = "";
            string message = "";

            while (true)
            {
                if (port.BytesToRead > 0)
                {
                    buffer += port.ReadExisting();

                    int start = buffer.IndexOf('>');

                    if (start != -1)
                    {
                        int end = buffer.IndexOf(';');
                        if (end != -1)
                        {
                            message = buffer.Substring(
                                start, (end - start) + 1);
                            buffer = buffer.Substring(end + 1);
                        }

                        if (message.Contains("BTN1"))
                        {
                            Console.SetCursorPosition(0, 0);
                            Console.Write(message.Substring(4, 1));
                        }
                        else if (message.Contains("FMEM"))
                        {
                            Console.SetCursorPosition(2, 0);
                            Console.Write(message.Substring(4, message.Length - 6));
                        }
                    }
                }
            }
        }
    }
}
