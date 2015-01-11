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

                    while (buffer.IndexOf('>') != -1)
                    {
                        int start = buffer.IndexOf('>');
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
                            Console.Write("    ");
                            Console.SetCursorPosition(2, 0);
                            Console.Write(message.Substring(5, message.Length - 6));
                        }
                    }

                    /* Check for buffer overflow
                    Console.SetCursorPosition(0, 1);
                    for (int i = 0; i < Console.WindowWidth; i++)
                    {
                        Console.Write(" ");
                    }
                    Console.SetCursorPosition(0, 1);
                    Console.Write(buffer);
                     */
                }
            }
        }
    }
}
