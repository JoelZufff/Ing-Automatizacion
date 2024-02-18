namespace Sistema_Almacen
{
    partial class Admin
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.TitleAdmin = new System.Windows.Forms.Label();
            this.MenuPrincipal = new System.Windows.Forms.Panel();
            this.DataTable = new System.Windows.Forms.DataGridView();
            this.Button2 = new System.Windows.Forms.Button();
            this.Button1 = new System.Windows.Forms.Button();
            this.BackButton = new System.Windows.Forms.Button();
            this.TextBox_NameFilter = new System.Windows.Forms.TextBox();
            this.TextB_Name = new System.Windows.Forms.Label();
            this.FilterPanel = new System.Windows.Forms.Panel();
            this.Button_New = new System.Windows.Forms.Button();
            this.Button_Erase = new System.Windows.Forms.Button();
            this.MenuPrincipal.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DataTable)).BeginInit();
            this.FilterPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // TitleAdmin
            // 
            this.TitleAdmin.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.TitleAdmin.AutoSize = true;
            this.TitleAdmin.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TitleAdmin.Location = new System.Drawing.Point(162, 12);
            this.TitleAdmin.Name = "TitleAdmin";
            this.TitleAdmin.Size = new System.Drawing.Size(214, 34);
            this.TitleAdmin.TabIndex = 0;
            this.TitleAdmin.Text = "Modo Administrador";
            this.TitleAdmin.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MenuPrincipal
            // 
            this.MenuPrincipal.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MenuPrincipal.Controls.Add(this.DataTable);
            this.MenuPrincipal.Controls.Add(this.Button2);
            this.MenuPrincipal.Controls.Add(this.Button1);
            this.MenuPrincipal.Location = new System.Drawing.Point(30, 105);
            this.MenuPrincipal.Name = "MenuPrincipal";
            this.MenuPrincipal.Size = new System.Drawing.Size(471, 298);
            this.MenuPrincipal.TabIndex = 2;
            // 
            // DataTable
            // 
            this.DataTable.AllowUserToAddRows = false;
            this.DataTable.AllowUserToDeleteRows = false;
            this.DataTable.AllowUserToResizeColumns = false;
            this.DataTable.AllowUserToResizeRows = false;
            this.DataTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.DataTable.BorderStyle = System.Windows.Forms.BorderStyle.None;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataTable.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.DataTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.DataTable.DefaultCellStyle = dataGridViewCellStyle2;
            this.DataTable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DataTable.Location = new System.Drawing.Point(0, 0);
            this.DataTable.MultiSelect = false;
            this.DataTable.Name = "DataTable";
            this.DataTable.ReadOnly = true;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataTable.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.DataTable.RowHeadersVisible = false;
            this.DataTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.DataTable.ShowCellErrors = false;
            this.DataTable.ShowCellToolTips = false;
            this.DataTable.ShowEditingIcon = false;
            this.DataTable.ShowRowErrors = false;
            this.DataTable.Size = new System.Drawing.Size(471, 298);
            this.DataTable.TabIndex = 4;
            this.DataTable.Visible = false;
            // 
            // Button2
            // 
            this.Button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button2.Location = new System.Drawing.Point(3, 152);
            this.Button2.Name = "Button2";
            this.Button2.Padding = new System.Windows.Forms.Padding(10);
            this.Button2.Size = new System.Drawing.Size(465, 141);
            this.Button2.TabIndex = 4;
            this.Button2.Text = "Productos";
            this.Button2.UseVisualStyleBackColor = true;
            this.Button2.Click += new System.EventHandler(this.ButtonProducts_Click);
            // 
            // Button1
            // 
            this.Button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button1.Location = new System.Drawing.Point(3, 5);
            this.Button1.Name = "Button1";
            this.Button1.Padding = new System.Windows.Forms.Padding(10);
            this.Button1.Size = new System.Drawing.Size(465, 141);
            this.Button1.TabIndex = 3;
            this.Button1.Text = "Clientes";
            this.Button1.UseVisualStyleBackColor = true;
            this.Button1.Click += new System.EventHandler(this.ButtonClients_Click);
            // 
            // BackButton
            // 
            this.BackButton.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BackButton.Location = new System.Drawing.Point(12, 12);
            this.BackButton.Name = "BackButton";
            this.BackButton.Size = new System.Drawing.Size(75, 23);
            this.BackButton.TabIndex = 3;
            this.BackButton.Text = "Volver";
            this.BackButton.UseVisualStyleBackColor = true;
            this.BackButton.Visible = false;
            this.BackButton.Click += new System.EventHandler(this.Back_Click);
            // 
            // TextBox_NameFilter
            // 
            this.TextBox_NameFilter.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TextBox_NameFilter.Location = new System.Drawing.Point(65, 3);
            this.TextBox_NameFilter.Name = "TextBox_NameFilter";
            this.TextBox_NameFilter.Size = new System.Drawing.Size(365, 20);
            this.TextBox_NameFilter.TabIndex = 4;
            this.TextBox_NameFilter.TextChanged += new System.EventHandler(this.TextBox_NameFilter_TextChanged);
            // 
            // TextB_Name
            // 
            this.TextB_Name.AutoSize = true;
            this.TextB_Name.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextB_Name.Location = new System.Drawing.Point(6, 4);
            this.TextB_Name.Name = "TextB_Name";
            this.TextB_Name.Size = new System.Drawing.Size(53, 17);
            this.TextB_Name.TabIndex = 5;
            this.TextB_Name.Text = "Nombre";
            // 
            // FilterPanel
            // 
            this.FilterPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FilterPanel.Controls.Add(this.TextBox_NameFilter);
            this.FilterPanel.Controls.Add(this.TextB_Name);
            this.FilterPanel.Location = new System.Drawing.Point(33, 69);
            this.FilterPanel.Name = "FilterPanel";
            this.FilterPanel.Size = new System.Drawing.Size(433, 30);
            this.FilterPanel.TabIndex = 6;
            this.FilterPanel.Visible = false;
            // 
            // Button_New
            // 
            this.Button_New.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.Button_New.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_New.Location = new System.Drawing.Point(168, 426);
            this.Button_New.Name = "Button_New";
            this.Button_New.Size = new System.Drawing.Size(75, 23);
            this.Button_New.TabIndex = 7;
            this.Button_New.Text = "Nuevo";
            this.Button_New.UseVisualStyleBackColor = true;
            this.Button_New.Visible = false;
            this.Button_New.Click += new System.EventHandler(this.Button_New_Click);
            // 
            // Button_Erase
            // 
            this.Button_Erase.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.Button_Erase.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_Erase.Location = new System.Drawing.Point(294, 426);
            this.Button_Erase.Name = "Button_Erase";
            this.Button_Erase.Size = new System.Drawing.Size(75, 23);
            this.Button_Erase.TabIndex = 8;
            this.Button_Erase.Text = "Borrar";
            this.Button_Erase.UseVisualStyleBackColor = true;
            this.Button_Erase.Visible = false;
            this.Button_Erase.Click += new System.EventHandler(this.Button_Erase_Click);
            // 
            // Admin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(534, 461);
            this.Controls.Add(this.Button_Erase);
            this.Controls.Add(this.Button_New);
            this.Controls.Add(this.FilterPanel);
            this.Controls.Add(this.BackButton);
            this.Controls.Add(this.MenuPrincipal);
            this.Controls.Add(this.TitleAdmin);
            this.MinimumSize = new System.Drawing.Size(550, 500);
            this.Name = "Admin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Administrador";
            this.Load += new System.EventHandler(this.Admin_Load);
            this.MenuPrincipal.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.DataTable)).EndInit();
            this.FilterPanel.ResumeLayout(false);
            this.FilterPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label TitleAdmin;
        private System.Windows.Forms.Panel MenuPrincipal;
        private System.Windows.Forms.Button Button1;
        private System.Windows.Forms.Button Button2;
        private System.Windows.Forms.Button BackButton;
        private System.Windows.Forms.DataGridView DataTable;
        private System.Windows.Forms.TextBox TextBox_NameFilter;
        private System.Windows.Forms.Label TextB_Name;
        private System.Windows.Forms.Panel FilterPanel;
        private System.Windows.Forms.Button Button_New;
        private System.Windows.Forms.Button Button_Erase;
    }
}