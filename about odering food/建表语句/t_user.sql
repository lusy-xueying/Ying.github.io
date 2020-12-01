USE [menu]
GO

/****** Object:  Table [dbo].[t_user]    Script Date: 2019/12/6 10:01:14 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[t_user](
	[id] [varchar](32) NOT NULL,
	[username] [varchar](50) NOT NULL,
	[password] [varchar](50) NOT NULL,
	[type] [int] NOT NULL,
	[isdelete] [int] NOT NULL,
 CONSTRAINT [PK_t_user] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[t_user] ADD  CONSTRAINT [DF_t_user_isdelete]  DEFAULT ((0)) FOR [isdelete]
GO

