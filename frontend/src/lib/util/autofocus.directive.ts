import {OnInit, ElementRef, Input, Directive} from '@angular/core';

@Directive({selector: '[focusMe]'})
export class FocusDirective implements OnInit {

    @Input('focusMe') isFocused: boolean;

    constructor(private element: ElementRef) {
    }

    ngOnInit() {
        if (this.isFocused) {
            this.element.nativeElement.focus();
        }
    }
}