using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graphic_interface
{

    public partial class TCP_connection : Form
    {
        private TcpClient client;
        static NetworkStream stream;

        public TCP_connection()
        {
            InitializeComponent();
            this.MaximizeBox = false;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;

            Show_Connection_Panel();
        }

        private void Show_Connection_Panel()
        {
            // Ocultamos todos los paneles que esten abiertos
            Panel_Graph.Visible = false;

            // Mostramos el panel con tamaño
            this.Size = new Size(270, 175);

            // Centrar ventana en la pantalla
            this.Location = new Point
            (
                (Screen.PrimaryScreen.WorkingArea.Width - this.Width) / 2,
                (Screen.PrimaryScreen.WorkingArea.Height - this.Height) / 2
            );

            Panel_Connection.Visible = true;
        }

        private void Show_Graph_Panel()
        {
            // Ocultamos todos los paneles que esten abiertos
            Panel_Connection.Visible = false;

            // Mostramos el panel con tamaño
            this.Size = new Size(800, 900);

            // Centrar ventana en la pantalla
            this.Location = new Point
            (
                (Screen.PrimaryScreen.WorkingArea.Width - this.Width) / 2,
                (Screen.PrimaryScreen.WorkingArea.Height - this.Height) / 2
            );

            Panel_Graph.Visible = true;
        }

        private async void Button_Connect_Click(object sender, EventArgs e)
        {
            // Conectar con servidor TCP, y si se conectar, ocultar pantalla y mostrar graficos
            try
            {
                client = new TcpClient();
                
                // Intento de conexion con timeout de 5 s
                var connectTask = client.ConnectAsync(Textbox_IP.Text, int.Parse(Textbox_Port.Text));
                if (await Task.WhenAny(connectTask, Task.Delay(5000)) != connectTask)
                    throw new TimeoutException("Tiempo de conexión agotado");

                stream = client.GetStream();

                // Iniciar recepción de datos en segundo plano
                _ = Task.Run(() => dataReception());

                // Mostramos panel de graficacion
                Show_Graph_Panel();
            }
            catch (SocketException sex)
            {
                MessageBox.Show($"Error de conexión: {sex.SocketErrorCode}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (TimeoutException tex)
            {
                MessageBox.Show(tex.Message, "Timeout", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error inesperado: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                if (client?.Connected == false)
                    client?.Dispose();
            }
        }

        private void processData(string receivedData)
        {
            richTextBox1.Text = receivedData;
        }

        private async Task dataReception()
        {
            try
            {
                while(client.Connected)
                {
                    List<byte> messageBuffer = new List<byte>();

                    byte[] buffer = new byte[1];
                    int bytesRead = await stream.ReadAsync(buffer, 0, 1);   // Leer un byte
                    
                    if (bytesRead == 0)
                        break;  // Conexion cerrada

                    if (buffer[0] == 0xAA)   // Caracter de inicio
                    {
                        messageBuffer.Clear();      // Limpiar buffer

                        // Leer los siguientes mensajes
                        for(int i = 0; i < 8; i++)
                        {
                            // Almacenar datos de variables
                        }
                    }
                }
            }
            catch(Exception ex)
            {

            }
        }
    }
}
