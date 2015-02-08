//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

//////////////////////////////////////////////////////////////////////////

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView;
@property (nonatomic, retain) IBOutlet EAGLView *glview;
@end

//////////////////////////////////////////////////////////////////////////