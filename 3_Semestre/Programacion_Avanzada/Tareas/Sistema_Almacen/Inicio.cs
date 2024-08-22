using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sistema_Almacen
{
    public partial class Principal : Form
    {
        //  Constructor  //
        public Principal()
        {
            InitializeComponent();
        }


        //  Metodos principales  //
        private void Principal_Load(object sender, EventArgs e) {}

        private void SendButton_Click(object sender, EventArgs e)
        {
            foreach(var Cliente in Variables.Lista_Clientes)
                if (Cliente.expediente == TextBoxExp.Text)
                {
                    if(Cliente.Ticket_Personal.Enabled)
                    {
                        Ticket Ticket_Actual = new Ticket(Variables.Lista_Clientes.IndexOf(Cliente));
                        Ticket_Actual.Show();
                    }
                    else
                    {
                        RegTicket Ticket_Window = new RegTicket(Variables.Lista_Clientes.IndexOf(Cliente));
                        Ticket_Window.Show();
                    }
                    TextBoxExp.Text = "";
                    return;
                }


            MessageBox.Show("El expediente ingresado no existe", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void getEXP_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
                SendButton.PerformClick();
            else if ((e.KeyChar >= 32 && e.KeyChar <= 47) || (e.KeyChar >= 58))
                e.Handled = true;                                               // Borra el caracter
        }

        private void AdminButton_Click(object sender, EventArgs e)
        {
            // Abir ventana de administrador
            AdminLogin Admin_Window = new AdminLogin();
            this.Enabled = false;
            Admin_Window.FormClosed += Window_FormClosed; // Enlazamos funcion con evento de cierre
            Admin_Window.Show();
        }

        private void RegistLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            // Abrir ventana de Registro
            RegistroCliente Regist_Window = new RegistroCliente();
            this.Enabled = false;
            Regist_Window.FormClosed += Window_FormClosed; // Enlazamos funcion con evento de cierre
            Regist_Window.Show();
        }

        //  Metodos auxiliares  //

        private void Window_FormClosed(object sender, FormClosedEventArgs e) { this.Enabled = true; }
    }
}