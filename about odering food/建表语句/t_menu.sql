USE [menu]
GO

/****** Object:  Table [dbo].[t_menu]    Script Date: 2019/12/6 10:01:37 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[t_menu](
	[id] [varchar](32) NOT NULL,
	[name] [varchar](100) NOT NULL,
	[price] [float] NULL,
	[pic] [varchar](200) NULL,
	[type] [int] NULL,
	[isdelete] [int] NOT NULL,
 CONSTRAINT [PK_t_menu] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[t_menu] ADD  CONSTRAINT [DF_t_menu_isdelete]  DEFAULT ((0)) FOR [isdelete]
GO

