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
    public partial class Admin : Form
    {
        string MenuSelected;
        DataTable Table = new DataTable();

        public Admin()
        {
            InitializeComponent();
            DataTable.DataSource = Table;
        }

        private void Admin_Load(object sender, EventArgs e) {}

        private void ButtonClients_Click(object sender, EventArgs e)
        {
            MenuSelected = "Clientes";

            TitleAdmin.Text = "  Admin Clientes";

            // Ocultamos los botones que no coresponden
            Button1.Visible = Button2.Visible = false;  
            
            // Mostramos los botones que corresponden
            BackButton.Visible = DataTable.Visible = FilterPanel.Visible = true;
            Button_New.Visible = Button_Erase.Visible = true;

            // Configuramos las columnas del DataGridView
            Table.Columns.Clear();      Table.Rows.Clear();
            Table.Columns.Add("Expediente", typeof(string));
            Table.Columns.Add("Nombre", typeof(string));
            Table.Columns.Add("Celular", typeof(string));
            Table.Columns.Add("Carrera", typeof(string));
            Table.Columns.Add("Estatus", typeof(string));

            // Llenamos las filas del DataGridView
            foreach(var Cliente in Variables.Lista_Clientes)
                Table.Rows.Add(Cliente.expediente, Cliente.nombre, Cliente.celular, Cliente.carrera, Cliente.estatus);

            if(Table.Rows.Count > 0)
                Button_Erase.Enabled = true;
            else
                Button_Erase.Enabled = false;

        }
        
        private void ButtonProducts_Click(object sender, EventArgs e)
        {
            MenuSelected = "Productos";

            TitleAdmin.Text = " Admin Productos";

            // Ocultamos los botones que no coresponden
            Button1.Visible = Button2.Visible = false;

            // Mostramos los botones que corresponden
            BackButton.Visible = DataTable.Visible = FilterPanel.Visible = true;
            Button_New.Visible = Button_Erase.Visible = true;

            // Configuramos las columnas del DataGridView
            Table.Columns.Clear(); Table.Rows.Clear();
            Table.Columns.Add("ID CODE", typeof(string));
            Table.Columns.Add("Nombre de Producto", typeof(string));
            Table.Columns.Add("Cantidad Total", typeof(int));
            Table.Columns.Add("Cantidad en Prestamo", typeof(int));

            // Llenamos las filas del DataGridView
            foreach (var Producto in Variables.Lista_Productos)
                Table.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, Producto.Cant_Total, Producto.Cant_Prestamo);

            if (Table.Rows.Count > 0)
                Button_Erase.Enabled = true;
            else
                Button_Erase.Enabled = false;
        }
        
        private void Back_Click(object sender, EventArgs e)
        {
            MenuSelected = ""; // Eliminamos seleccion de menu

            TitleAdmin.Text = "Modo Administracion";

            // Mostramos elementos correspondientes y reseteamos Textbox
            Button1.Visible = Button2.Visible = true;
            BackButton.Visible = DataTable.Visible = FilterPanel.Visible = false;
            Button_New.Visible = Button_Erase.Visible = false;
            TextBox_NameFilter.Text = "";
        }

        private void TextBox_NameFilter_TextChanged(object sender, EventArgs e)
        {
            // En funcion del menu actual, el filtro de nombre rellenara las filas

            Table.Rows.Clear(); // Limpiamos datos actuales, pues se modifico un filtro

            switch (MenuSelected)
            {
                case "Clientes":
                {
                    foreach (var Cliente in Variables.Lista_Clientes)
                        // Convertimos a minuscula para despreciar diferencias de letras minusculas y mayusculas
                        if (Cliente.nombre.ToLower().Contains(TextBox_NameFilter.Text.ToLower()))           // Si coincide el nombre agregar a la vista
                            Table.Rows.Add(Cliente.expediente, Cliente.nombre, Cliente.celular, Cliente.carrera, Cliente.estatus);
                }
                    break;
                case "Productos":
                {
                    foreach (var Producto in Variables.Lista_Productos)
                        // Convertimos a minuscula para despreciar diferencias de letras minusculas y mayusculas
                        if (Producto.Nombre_Producto.ToLower().Contains(TextBox_NameFilter.Text.ToLower())) // Si coincide el nombre agregar a la vista
                            Table.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, Producto.Cant_Total, Producto.Cant_Prestamo);
                }
                    break;
                default: break;
            }

            if (Table.Rows.Count > 0)
                Button_Erase.Enabled = true;
            else
                Button_Erase.Enabled = false;
        }

        private void Button_Erase_Click(object sender, EventArgs e)
        {   
            DialogResult Answer = MessageBox.Show("¿Esta seguro que desea eliminar el elemento seleccionado?", "Confirmacion" , MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (Answer == DialogResult.No)
                return;

            switch(MenuSelected)
            {
                case "Clientes":
                {
                    // Obtenemos expediente de cliente seleccionado
                    string Expediente = DataTable.CurrentRow.Cells[0].Value.ToString();

                    // Eliminamos Cliente en lista de clientes
                    foreach (var Cliente in Variables.Lista_Clientes)
                        if (Cliente.expediente == Expediente) { Variables.Lista_Clientes.Remove(Cliente); break; }

                    // Eliminamos Cliente en DataTable mostrado
                    foreach (DataRow Row in Table.Rows)
                        if (Row[0].ToString() == Expediente) { Row.Delete(); break; }
                }
                    break;
                case "Productos":
                {
                    // Obtenemos expediente de cliente seleccionado
                    string ID = DataTable.CurrentRow.Cells[0].Value.ToString();

                    // Eliminamos Producto en lista de clientes
                    foreach (var Producto in Variables.Lista_Productos)
                        if (Producto.ID_CODE == ID) { Variables.Lista_Productos.Remove(Producto); break; }

                    // Eliminamos Cliente en DataTable mostrado
                    foreach (DataRow Row in Table.Rows)
                        if (Row[0].ToString() == ID) { Row.Delete(); break; }
                }
                    break;
                default: break;
            }

            if (Table.Rows.Count == 0)
                Button_Erase.Enabled = false;

            MessageBox.Show("El elemento ha sido eliminado exitosamente", "Exito", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Button_New_Click(object sender, EventArgs e)
        {
            switch (MenuSelected)
            {
                case "Clientes":
                {
                    RegistroCliente Window = new RegistroCliente();
                    Window.Show();
                }
                    break;
                case "Productos":
                {
                    // Abrir ventana de registro de producto    
                }
                    break;
                default: break;
            }
        }
    }
}

// Bloquear ventana al abrir registro